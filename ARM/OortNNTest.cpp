#include "utils.h"
#include "./lib/opennn/opennn.h"

using namespace OpenNN;

int main(int argc, char const *argv[]) {

    try {
        DataSet ds;
        ds.set_data_file_name("./res/knl/data.knl");
        ds.set_separator("Semicolon");
        ds.load_data();

        Variables* vars = ds.get_variables_pointer();

        vars->set_name(0, "in1");
        vars->set_use(0, Variables::Input);
        vars->set_name(1, "in2");
        vars->set_use(1, Variables::Input);
        vars->set_name(2, "in3");
        vars->set_use(2, Variables::Input);
        vars->set_name(3, "in4");
        vars->set_use(3, Variables::Input);
        vars->set_name(4, "out1");
        vars->set_use(4, Variables::Target);

        const Matrix<string> inInfo = vars->get_inputs_information();
        const Matrix<string> tarInfo = vars->get_targets_information();

        // Instances.
        Instances* insts = ds.get_instances_pointer();
        insts->split_random_indices();
        const Vector<Statistics<double>> inStats = ds.scale_inputs_minimum_maximum();

        // Neural network.
        NeuralNetwork nn(4, 6, 1);
        nn.get_multilayer_perceptron_pointer()->get_layer_pointer(0)->set_activation_function(PerceptronLayer::ActivationFunction::Logistic);
        nn.get_multilayer_perceptron_pointer()->get_layer_pointer(1)->set_activation_function(PerceptronLayer::ActivationFunction::Logistic);
        // nn.save("./sav/neural_network.xml");

        // Inputs* ins = nn.get_inputs_pointer();
        // ins->set_information(inInfo);
        //
        // Outputs* outs = nn.get_outputs_pointer();
        // outs->set_information(tarInfo);
        nn.save("./sav/neural_network.xml");

        // nn.construct_scaling_layer();
        // ScalingLayer* scalLayer = nn.get_scaling_layer_pointer();
        // scalLayer->set_statistics(inStats);
        // scalLayer->set_scaling_methods(ScalingLayer::NoScaling);

        // Training strategy.
        TrainingStrategy trainStrat(&nn, &ds);
        trainStrat.set_training_method(TrainingStrategy::GRADIENT_DESCENT);
        GradientDescent* qNMethod = trainStrat.get_gradient_descent_pointer();
        qNMethod->set_minimum_loss_decrease(1.0e-6);
        qNMethod->perform_training();
        trainStrat.set_display(false);

        // Testing analysis.
        // TestingAnalysis testAnalysis(&nn, &ds);
        // const Matrix<size_t> confusion = testAnalysis.calculate_confusion();


        // Save results.
        // ds.save("./sav/data_set.xml");
        nn.save("./sav/neural_network.xml");
        nn.save_expression("./sav/expression.txt");
        // trainStrat.save("./sav/training_strategy.xml");
        // confusion.save("./sav/confusion.dat");

        return 0;
    } catch (exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}
