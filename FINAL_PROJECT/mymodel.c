//#include <stdio.h>
//#include <stdlib.h>
#include <math.h>
//#include <errno.h>
#include <sodium.h> 
#include <string.h>

#include "mymodel.h"
//#include "constants.h"

double cost_train;
double accuracy_train;

//------------------------------------------------------sigmoid implementation-------------------------------------------------------------
double sigmoid(double x) {
    // Implementation of the sigmoid activation function
    return 1.0 / (1.0 + exp(-x));
}

//---------------------------------------------------random_double implementation---------------------------------------------------
double random_double(double min, double max)
{
    unsigned char buffer[sizeof(uint64_t)]; // Buffer to hold random bytes
    uint64_t random_value;

    // Initialize the sodium library
    if (sodium_init() < 0) {
        // Initialization failed
        // Handle the error here (e.g., print an error message and exit)
    }

    // Generate random bytes
    randombytes_buf(buffer, sizeof(uint64_t));

    // Convert the random bytes to a 64-bit unsigned integer value
    memcpy(&random_value, buffer, sizeof(uint64_t));

    // Scale the 64-bit random integer to a double value in the range [0, 1.0]
    double scale = random_value / ((double)UINT64_MAX);

    // Scale the value to the desired range [min, max]
    return min + scale * (max - min);
}

//------------------------------------------------------------readDataFromFile implementation------------------------------------------------------------
int readDataFromFile(const char *filename, double data[MAX_ROWS][MAX_COLS]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    int row = 0;
    char line[100];

    printf("Reading file.\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%lf %lf %lf %lf", &data[row][0], &data[row][1], &data[row][2], &data[row][3]);
        row++;
        if (row >= MAX_ROWS) {
            printf("End of the file.\n");
            break;
        }
    }

    printf("Reading file done.\n");
    fclose(file);
    return 0;
}

//-----------------------------------------------------------CreateDataset implementation-----------------------------------------------------------------
void CreateDataset(double X_train[][num_inputs], double Y_train[][num_outputs],
                   double X_val[][num_inputs], double Y_val[][num_outputs], double data[][MAX_COLS],
                   int num_train) {
    for (int row = 0; row < num_train; row++) {
        X_train[row][0] = data[row][0];
        X_train[row][1] = data[row][1];
        Y_train[row][0] = data[row][2];
        Y_train[row][1] = data[row][3];
    }

    for (int row = num_train; row < MAX_ROWS; row++) {
        X_val[row - num_train][0] = data[row][0];
        X_val[row - num_train][1] = data[row][1];
        Y_val[row - num_train][0] = data[row][2];
        Y_val[row - num_train][1] = data[row][3];
    }
}

//-----------------------------------------------------ForwardPass implementation--------------------------------------------------------------------------
void ForwardPass(int num_train, double X_train[][num_inputs], double Y_train[][num_outputs],
                 double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                 double b2[][1], double b3[][1], double b4[][1],
                 double a2[][num_train], double a3[][num_train], double a4[][num_train])
{

    for (int i = 0; i < num_neurons_layer2; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < num_inputs; k++)
            {
                sum += W2[i][k] * X_train[j][k];
            }

            a2[i][j] = tanh(sum + b2[i][0]); // the activation function here is tanh()
        }
    }

    for (int i = 0; i < num_neurons_layer3; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < num_neurons_layer2; k++)
            {
                sum += W3[i][k] * a2[k][j];
            }

            a3[i][j] = tanh(sum + b3[i][0]); // the activation function here is tanh()
        }
    }

    for (int i = 0; i < num_outputs; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < num_neurons_layer3; k++)
            {
                sum += W4[i][k] * a3[k][j];
            }

            a4[i][j] = sigmoid(sum + b4[i][0]);
        }
    }
}

//----------------------------------------------------BackwardPass implementation---------------------------------------------------------
void backwardPass(int num_train,
                  double X_train[][num_inputs], double Y_train[][num_outputs],
                  double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                  double a2[][num_train], double a3[][num_train], double a4[][num_train],
                  double b2[][1], double b3[][1], double b4[][1])
{
    double PL1[num_neurons_layer2][num_train];
    double PL2[num_neurons_layer3][num_train];
    double PL3[num_outputs][num_train];

    // Calculate PL2 = (a4 - Y_train).*(1-a4).*a4 if the activation function is sigmoid() in the output layer
    for (int i = 0; i < num_outputs; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            PL3[i][j] = (a4[i][j] - Y_train[j][i]) * (1 - a4[i][j]) * a4[i][j];
        }
    }

    // Calculate PL2 = (1 - H3.^2) .* (W4' * PL3) if the activation function is tanh() in layer 3
    double a3_squared_complement[num_neurons_layer3][num_train];
    for (int i = 0; i < num_neurons_layer3; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            a3_squared_complement[i][j] = 1 - a3[i][j] * a3[i][j];
        }
    }

    double W4_PL3[num_neurons_layer3][num_train];
    for (int i = 0; i < num_neurons_layer3; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < num_outputs; k++)
            {
                sum += W4[k][i] * PL3[k][j];
            }
            W4_PL3[i][j] = sum;
        }
    }

    for (int i = 0; i < num_neurons_layer3; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            PL2[i][j] = a3_squared_complement[i][j] * W4_PL3[i][j];
        }
    }

    // Calculate PE1 = (1 - H2.^2) .* (W3' * PE2) if the activation function is tanh() in layer 2
    double a2_squared_complement[num_neurons_layer2][num_train];
    for (int i = 0; i < num_neurons_layer2; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            a2_squared_complement[i][j] = 1 - a2[i][j] * a2[i][j];
        }
    }

    double W3_PL2[num_neurons_layer2][num_train];
    for (int i = 0; i < num_neurons_layer2; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < num_neurons_layer3; k++)
            {
                sum += W3[k][i] * PL2[k][j];
            }
            W3_PL2[i][j] = sum;
        }
    }

    for (int i = 0; i < num_neurons_layer2; i++)
    {
        for (int j = 0; j < num_train; j++)
        {
            PL1[i][j] = a2_squared_complement[i][j] * W3_PL2[i][j];
        }
    }

    // Update weights and biases using Learning_rate
    for (int i = 0; i < num_neurons_layer2; i++)
    {
        for (int j = 0; j < num_inputs; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < num_train; k++)
            {
                sum += PL1[i][k] * X_train[k][j];
            }
            W2[i][j] -= Learning_rate * sum;
        }
    }

    for (int i = 0; i < num_neurons_layer3; i++)
    {
        for (int j = 0; j < num_neurons_layer2; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < num_train; k++)
            {
                sum += PL2[i][k] * a2[j][k];
            }
            W3[i][j] -= Learning_rate * sum;
        }
    }

    for (int i = 0; i < num_outputs; i++)
    {
        for (int j = 0; j < num_neurons_layer3; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < num_train; k++)
            {
                sum += PL3[i][k] * a3[j][k];
            }
            W4[i][j] -= Learning_rate * sum;
        }
    }

    // Update biases b2, b3, and b4
    for (int i = 0; i < num_neurons_layer2; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < num_train; j++)
        {
            sum += PL1[i][j];
        }
        b2[i][0] -= Learning_rate * sum;
    }

    for (int i = 0; i < num_neurons_layer3; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < num_train; j++)
        {
            sum += PL2[i][j];
        }
        b3[i][0] -= Learning_rate * sum;
    }

    for (int i = 0; i < num_outputs; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < num_train; j++)
        {
            sum += PL3[i][j];
        }
        b4[i][0] -= Learning_rate * sum;
    }
}

//-----------------------------------------------------InitializeWeightsAndBiases implementation-------------------------------------------------
void InitializeWeightsAndBiases(double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                                double b2[][1], double b3[][1], double b4[][1]) {
    // Initialize W2 and b2 arrays with random values between -a and +a
    for (int i = 0; i < num_neurons_layer2; i++) {
        for (int j = 0; j < num_inputs; j++) {
            W2[i][j] = random_double(-initial_range, initial_range);
        }
        b2[i][0] = random_double(-initial_range, initial_range);
    }

    // Initialize W3 and b3 arrays with random values between -a and +a
    for (int i = 0; i < num_neurons_layer3; i++) {
        for (int j = 0; j < num_neurons_layer2; j++) {
            W3[i][j] = random_double(-initial_range, initial_range);
        }
        b3[i][0] = random_double(-initial_range, initial_range);
    }

    // Initialize W4 and b4 arrays with random values between -a and +a
    for (int i = 0; i < num_outputs; i++) {
        for (int j = 0; j < num_neurons_layer3; j++) {
            W4[i][j] = random_double(-initial_range, initial_range);
        }
        b4[i][0] = random_double(-initial_range, initial_range);
    }
}

//-------------------------------------------------------------------------------------Evaluation implementation-----------------------------------------------------------------------
void Evaluation(int ep, int num_train, int num_val,
                double X_train[][num_inputs], double Y_train[][num_outputs],
                double X_val[][num_inputs], double Y_val[][num_outputs],
                double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                double b2[][1], double b3[][1], double b4[][1],
                double a2[][num_train], double a3[][num_train]) {

    double a4_eval_train[num_outputs][num_train];
    ForwardPass(num_train, X_train, Y_train, W2, W3, W4, b2, b3, b4, a2, a3, a4_eval_train);

    int correct_predictions = 0;
    for (int i = 0; i < num_train; i++) {
        int all_correct = 1; // Assume all outputs are correct for this example
        for (int j = 0; j < num_outputs; j++) {
            if ((a4_eval_train[j][i] >= 0.5 && Y_train[i][j] == 0) || (a4_eval_train[j][i] < 0.5 && Y_train[i][j] == 1)) {
                all_correct = 0; // Found an incorrect prediction for this example
                break;
            }
        }
        correct_predictions += all_correct;
    }

    double accuracy_train = (double)correct_predictions / num_train * 100.0;

    double sum_squared_diff = 0.0;
    for (int i = 0; i < num_train; i++) {
        for (int j = 0; j < num_outputs; j++) {
            double diff = Y_train[i][j] - a4_eval_train[j][i]; // Transpose a4_eval_train by switching indices
            sum_squared_diff += diff * diff;
        }
    }

    // Calculate the cost and divide by num_train
    double cost_train = sum_squared_diff / num_train;

    // Dynamically allocate memory for validation evaluation
    double(*a2_val)[num_val] = malloc(num_neurons_layer2 * sizeof(double[num_val]));
    double(*a3_val)[num_val] = malloc(num_neurons_layer3 * sizeof(double[num_val]));
    double(*a4_val)[num_val] = malloc(num_outputs * sizeof(double[num_val]));

    ForwardPass(num_val, X_val, Y_val, W2, W3, W4, b2, b3, b4, a2_val, a3_val, a4_val);

    correct_predictions = 0;
    for (int i = 0; i < num_val; i++) {
        int all_correct = 1; // Assume all outputs are correct for this example
        for (int j = 0; j < num_outputs; j++) {
            if ((a4_val[j][i] >= 0.5 && Y_val[i][j] == 0) || (a4_val[j][i] < 0.5 && Y_val[i][j] == 1)) {
                all_correct = 0; // Found an incorrect prediction for this example
                break;
            }
        }
        correct_predictions += all_correct;
    }

    double accuracy_val = (double)correct_predictions / num_val * 100.0;

    sum_squared_diff = 0.0;
    for (int i = 0; i < num_val; i++) {
        for (int j = 0; j < num_outputs; j++) {
            double diff = Y_val[i][j] - a4_val[j][i]; // Transpose a4_eval_train by switching indices
            sum_squared_diff += diff * diff;
        }
    }

    free(a2_val);
    free(a3_val);
    free(a4_val);

    // Calculate the cost and divide by num_train
    double cost_val = sum_squared_diff / num_val;

    // Print results with epoch number
    printf("epoch %d:\n", ep);
    printf("Train Cost      %lf,    Accuracy: %.2f%%\n", cost_train, accuracy_train);
    printf("Validation Cost %lf,    Accuracy: %.2f%%\n\n", cost_val, accuracy_val);
}


