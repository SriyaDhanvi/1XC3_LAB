#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "mymodel.h"

int main()
{
    // Open the file in read mode
    double data[MAX_ROWS][MAX_COLS];

    if (readDataFromFile("data.txt", data) != 0) {
        return 1;
    }

    int num_train = MAX_ROWS *train_split;
    int num_val = MAX_ROWS *(1-train_split);
    // int num_train = 120;
    // int num_val = MAX_ROWS - 120;

    double X_train[num_train][num_inputs];
    double Y_train[num_train][num_outputs];
    double X_val[num_val][num_inputs];
    double Y_val[num_val][num_outputs];

    CreateDataset(X_train, Y_train, X_val, Y_val, data, num_train);

    double W2[num_neurons_layer2][num_inputs];
    double b2[num_neurons_layer2][1];

    double W3[num_neurons_layer3][num_neurons_layer2];
    double b3[num_neurons_layer3][1];

    double W4[num_outputs][num_neurons_layer3];
    double b4[num_outputs][1];

    


    
    // Initialize W2 and b2 arrays with random values between -a and +a
    InitializeWeightsAndBiases(W2, W3, W4, b2, b3, b4);

    // the final output of each layer, every column is for a set of inputs
    double a2[num_neurons_layer2][num_train];
    double a3[num_neurons_layer3][num_train];
    double a4[num_outputs][num_train];

    

    for (int ep = 0; ep < epochs; ep++)
    {
        // ###################################################### ForwardPass start
        

        ForwardPass(num_train, X_train, Y_train,
                    W2, W3, W4,
                    b2, b3, b4,
                    a2, a3, a4);
        // ###################################################### end of ForwardPass

        // ###################################################### BackwardPass start
        backwardPass(num_train, X_train, Y_train, W2, W3, W4, a2, a3, a4, b2, b3, b4);


        // ###################################################### end of BackwardPass

        // QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
        // ###################################################### Evaluation of accuracies starts

        if (ep%100==0)
        {
            Evaluation(ep, num_train, num_val,
                   X_train, Y_train, X_val, Y_val,
                   W2, W3, W4, b2, b3, b4, a2, a3);
        }
    }
}
