#ifndef MYMODEL_H
#define MYMODEL_H

//#include <stdint.h>
//#include <stdlib.h>
#include "constants.h"

extern double cost_train;
extern double accuracy_train;

double sigmoid(double x);

double random_double(double min, double max);

int readDataFromFile(const char *filename, double data[MAX_ROWS][MAX_COLS]);

void CreateDataset(double X_train[][num_inputs], double Y_train[][num_outputs],
                   double X_val[][num_inputs], double Y_val[][num_outputs], double data[][MAX_COLS],
                   int num_train);

void ForwardPass(int num_train, double X_train[][num_inputs], double Y_train[][num_outputs],
                 double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                 double b2[][1], double b3[][1], double b4[][1],
                 double a2[][num_train], double a3[][num_train], double a4[][num_train]);

void backwardPass(int num_train,
                  double X_train[][num_inputs], double Y_train[][num_outputs],
                  double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                  double a2[][num_train], double a3[][num_train], double a4[][num_train],
                  double b2[][1], double b3[][1], double b4[][1]);

void InitializeWeightsAndBiases(double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                                double b2[][1], double b3[][1], double b4[][1]);

void Evaluation(int ep, int num_train, int num_val,
                double X_train[][num_inputs], double Y_train[][num_outputs],
                double X_val[][num_inputs], double Y_val[][num_outputs],
                double W2[][num_inputs], double W3[][num_neurons_layer2], double W4[][num_neurons_layer3],
                double b2[][1], double b3[][1], double b4[][1],
                double a2[][num_train], double a3[][num_train]);

#endif /* MYMODEL_H */

