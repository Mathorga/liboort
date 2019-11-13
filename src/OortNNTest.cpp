#include "utils.h"
#include "../lib/opennn/opennn.h"

// using namespace OpenNN;

int main(int argc, char const *argv[]) {

    try {
        // Define layers' sizes.
        OpenNN::Vector<size_t> layersSizes(3);
        layersSizes[0] = 5;
        layersSizes[1] = 10;
        layersSizes[2] = 3;

        // Define layers' activation funcions.
        // Activation funcions do not apply to output layers, so they're only set for the first two layers.
        OpenNN::Vector<OpenNN::PerceptronLayer::ActivationFunction> activations(2);
        activations[0] = OpenNN::PerceptronLayer::Logistic;
        activations[1] = OpenNN::PerceptronLayer::Logistic;

        // Create the network given the sizes of all layers.
        OpenNN::MultilayerPerceptron* network = new OpenNN::MultilayerPerceptron(layersSizes);

        // Set network's activation functions for each layer.
        network->set_layers_activation_function(activations);


        
        std::cout << network->object_to_string();
        // OpenNN::MultilayerPerceptron* network = new OpenNN::MultilayerPerceptron(layersSizes);
        //
        // OpenNN::Vector<OpenNN::MultilayerPerceptron::LayerActivationFunction> hiddenLayersActivations(3, OpenNN::MultilayerPerceptron::Logistic);
        // network->set_layers_activation_function(hiddenLayersActivations);

        // network->print();


        // DataSet ds;
        // ds.set_data_file_name("./res/knl/data.knl");
        // ds.set_separator("Semicolon");
        // ds.load_data();
        //
        // Variables* vars = ds.get_variables_pointer();
        //
        // vars->set_name(0, "in1");
        // vars->set_use(0, Variables::Input);
        // vars->set_name(1, "in2");
        // vars->set_use(1, Variables::Input);
        // vars->set_name(2, "in3");
        // vars->set_use(2, Variables::Input);
        // vars->set_name(3, "in4");
        // vars->set_use(3, Variables::Input);
        // vars->set_name(4, "out1");
        // vars->set_use(4, Variables::Target);
        //
        // const Matrix<string> inInfo = vars->get_inputs_information();
        // const Matrix<string> tarInfo = vars->get_targets_information();
        //
        // // Instances.
        // Instances* insts = ds.get_instances_pointer();
        // insts->split_random_indices();
        // const Vector<Statistics<double>> inStats = ds.scale_inputs_minimum_maximum();
        //
        // // Neural network.
        // NeuralNetwork nn(4, 6, 1);
        // nn.get_multilayer_perceptron_pointer()->get_layer_pointer(0)->set_activation_function(PerceptronLayer::ActivationFunction::Logistic);
        // nn.get_multilayer_perceptron_pointer()->get_layer_pointer(1)->set_activation_function(PerceptronLayer::ActivationFunction::Logistic);
        // // nn.save("./sav/neural_network.xml");
        //
        // // Inputs* ins = nn.get_inputs_pointer();
        // // ins->set_information(inInfo);
        // //
        // // Outputs* outs = nn.get_outputs_pointer();
        // // outs->set_information(tarInfo);
        // nn.save("./sav/neural_network.xml");
        //
        // // nn.construct_scaling_layer();
        // // ScalingLayer* scalLayer = nn.get_scaling_layer_pointer();
        // // scalLayer->set_statistics(inStats);
        // // scalLayer->set_scaling_methods(ScalingLayer::NoScaling);
        //
        // // Training strategy.
        // TrainingStrategy trainStrat(&nn, &ds);
        // trainStrat.set_training_method(TrainingStrategy::GRADIENT_DESCENT);
        // GradientDescent* qNMethod = trainStrat.get_gradient_descent_pointer();
        // qNMethod->set_minimum_loss_decrease(1.0e-6);
        // qNMethod->perform_training();
        // trainStrat.set_display(false);
        //
        // // Testing analysis.
        // // TestingAnalysis testAnalysis(&nn, &ds);
        // // const Matrix<size_t> confusion = testAnalysis.calculate_confusion();
        //
        //
        // // Save results.
        // // ds.save("./sav/data_set.xml");
        // nn.save("./sav/neural_network.xml");
        // nn.save_expression("./sav/expression.txt");
        // // trainStrat.save("./sav/training_strategy.xml");
        // // confusion.save("./sav/confusion.dat");

        return 0;
    } catch (exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}
