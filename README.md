# MachineLearningVoter
*Uses 3 Supervised and 2 Unsupervised Machine Learning Algorithms to parse through 2 voter files and either predict a vote or generate clusters*

The 3 Supervised algorithms include K-Nearest Neighbor, Perceptron and ID3 Decision Tree. 
The 2 Unsupervised algorithms include K-Means and Agglomerative Clustering (AGNES).

The supervised algorithms were designed **specifically** for the parsing of the voter training data. 
Because there were 9 different attributes and 1 label in the data, the data was simply parsed into different variables.

## K-Nearest-Neighbor(KNN)

Included is the header file and cpp file.
The implementation is as follows:
  1. The Euclidean distance between a county's data (testing set) and every other county's data (training set) was found
  2. The top 10 counties with the smallest Euclidean distance from the inputted county data was retrieved
  3. The average of the votes (Democratic/Republican) was then used to predict the vote that the input county would make.
  
The KNN algorithm produced an accuracy rating of *87.96%*
  
## Perceptron

Included is the header file and cpp file.
The implementation is as follows:
  1. The label value that the Perceptron will produce should be 0 or 1
    1. 0 indicating a Republican vote, 1 indicating a Democratic vote
  2. Weights for each of the attributes are initialized
    1. Since the data was known, very specific weights were used to normalize each attribute
  3. Using the training set, the weights were modified to fit the data
    1. The difference between the prediction and the actual vote, a specified growth rate and the weight itself were used in this modification
    2. If the prediction was too high, it would be lowered. If it was too low, it would be raised.
  4. When determining the vote of a testing County data set, it's set of values were dot-producted with the approprates weights and the value was rounded to either 0 or 1 to determine the vote type
  
The Perceptron algorithm produced an accuracy rating of *86.55%*
