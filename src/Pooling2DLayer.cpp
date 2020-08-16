#include "Pooling2DLayer.h"

namespace oort {
    Pooling2DLayer::Pooling2DLayer(const uint32_t inWidth,
                                   const uint32_t inHeight,
                                   const uint32_t channelsNum,
                                   const uint32_t poolWidth,
                                   const uint32_t poolHeight) :
    PoolingLayer(inWidth * inHeight * channelsNum,
                 (inWidth / poolWidth) * (inHeight / poolHeight) * channelsNum,
                 channelsNum) {
        // Set default stride to pool width in order not to overlap pool samples.
        this->horizontalStride = poolWidth;
        this->verticalStride = poolHeight;

        // Set padding.
        this->horizontalPadding = 0;
        this->verticalPadding = 0;

        // Set accepted input width.
        this->inWidth = inWidth;

        // Set accepted input height.
        this->inHeight = inHeight;

        // Set filter width.
        this->poolWidth = poolWidth;

        // Set filter height.
        this->poolHeight = poolHeight;

        // Set default pooling function to MAX.
        this->poolingFunction = PoolingFunction::MAX;

        // Allocate composed values.
        math::alloc(&(this->composedValues), inWidth / poolWidth, inHeight / poolHeight, channelsNum);

        // Allocate activated values.
        math::alloc(&(this->activatedValues), inWidth / poolWidth, inHeight / poolHeight, channelsNum);

        // Define activation function.
        this->activationFunction = new math::Identity();
    }

    Pooling2DLayer::Pooling2DLayer(const uint32_t horizontalStride,
                                   const uint32_t verticalStride,
                                   const uint32_t horizontalPadding,
                                   const uint32_t verticalPadding,
                                   const uint32_t inWidth,
                                   const uint32_t inHeight,
                                   const uint32_t channelsNum,
                                   const uint32_t poolWidth,
                                   const uint32_t poolHeight,
                                   const PoolingFunction poolingFunction,
                                   math::DUnFunc* activationFunction) :
    PoolingLayer(inWidth * inHeight * channelsNum,
                 ((inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride) * ((inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride) * channelsNum,
                 channelsNum) {
        // Set stride.
        this->horizontalStride = horizontalStride;
        this->verticalStride = verticalStride;

        // Set padding.
        this->horizontalPadding = horizontalPadding;
        this->verticalPadding = verticalPadding;

        // Set accepted input width.
        this->inWidth = inWidth;

        // Set accepted input height.
        this->inHeight = inHeight;

        // Set filter width.
        this->poolWidth = poolWidth;

        // Set filter height.
        this->poolHeight = poolHeight;

        // Set pooling function.
        this->poolingFunction = poolingFunction;

        // Allocate composed values.
        math::alloc(&(this->composedValues),
                    (inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride,
                    (inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride,
                    channelsNum);

        // Allocate activated values.
        math::alloc(&(this->activatedValues),
                    (inWidth - poolWidth + horizontalPadding + horizontalStride) / horizontalStride,
                    (inHeight - poolHeight + verticalPadding + verticalStride) / verticalStride,
                    channelsNum);

        // Define activation function.
        this->activationFunction = activationFunction;
    }

    void Pooling2DLayer::step(const math::dtensor input) {
        // Create a temporary 3D input tensor of dimensions inWidth, inHeight, channelsNum.
        math::dtensor3d input3d;
        math::alloc(&input3d, this->inWidth, this->inHeight, this->channelsNum);

        // Copy general input tensor to temporary 3D tensor.
        math::copy(input3d, input);

        // Temporary out size.
        uint32_t outWidth = (this->inWidth - this->poolWidth + this->horizontalPadding + this->horizontalStride) / this->horizontalStride;
        uint32_t outHeight = (this->inHeight - this->poolHeight + this->verticalPadding + this->verticalStride) / this->verticalStride;

        // Loop through channels.
        for (uint32_t channel = 0; channel < input3d.depth; channel++) {
            // Loop through input columns.
            for (uint32_t col = 0; col < this->inWidth; col += this->poolWidth) {
                // Loop through input rows.
                for (uint32_t row = 0; row < this->inHeight; row += this->poolHeight) {
                    // Compute current output row and column.
                    uint32_t outRow = (row - this->poolWidth + this->horizontalPadding + this->horizontalStride) / this->horizontalStride;
                    uint32_t outCol = (col - this->poolHeight + this->verticalPadding + this->verticalStride) / this->verticalStride;

                    // Set composed values by applying pooling function over pool.
                    switch (this->poolingFunction) {
                        case MAX:
                            this->composedValues.values[IDX3D(outRow, outCol, channel, outWidth, outHeight)] = this->maxPool(input3d, channel, col, row);
                            break;
                        case AVG:
                            this->composedValues.values[IDX3D(outRow, outCol, channel, outWidth, outHeight)] = this->avgPool(input3d, channel, col, row);
                            break;
                        case MIN:
                            this->composedValues.values[IDX3D(outRow, outCol, channel, outWidth, outHeight)] = this->minPool(input3d, channel, col, row);
                            break;
                        case MED:
                            this->composedValues.values[IDX3D(outRow, outCol, channel, outWidth, outHeight)] = this->medPool(input3d, channel, col, row);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        utils::print(input3d);
        utils::print(this->composedValues);

        // Activate layer.
        math::prim(this->activatedValues, this->composedValues, this->activationFunction);

        // Free temporary tensor.
        math::dealloc(input3d);
    }

    void Pooling2DLayer::backprop() {}
    void Pooling2DLayer::print() {}

    double Pooling2DLayer::maxPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow) {
        double max = 0;

        // Horizontally loop through the pool.
        for (uint32_t column = startColumn; column < startColumn + this->poolWidth; column++) {
            // Vertically loop through the pool.
            for (uint32_t row = startRow; row < startRow + this->poolHeight; row++) {
                // Fetch the current value.
                double currentValue = input.values[IDX3D(row, column, channel, this->inWidth, this->inHeight)];

                // Check if the current value is greater than the last max.
                if (currentValue > max) {
                    // Update the overall max.
                    max = currentValue;
                }
            }
        }

        return max;
    }

    double Pooling2DLayer::avgPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow) {
        double sum = 0;

        // Horizontally loop through the pool.
        for (uint32_t column = startColumn; column < startColumn + this->poolWidth; column++) {
            // Vertically loop through the pool.
            for (uint32_t row = startRow; row < startRow + this->poolHeight; row++) {
                // Fetch the current value and add it to the sum.
                sum += input.values[IDX3D(row, column, channel, this->inWidth, this->inHeight)];
            }
        }

        // Return the average on the pool size.
        return sum / (this->poolWidth * this->poolHeight);
    }

    double Pooling2DLayer::minPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow) {}

    double Pooling2DLayer::medPool(const math::dtensor3d input, const uint32_t channel, const uint32_t startColumn, const uint32_t startRow) {}

    uint32_t Pooling2DLayer::getHorizontalStride() {
        return this->horizontalStride;
    }
}