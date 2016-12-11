# MachineLearningVoter
*Uses 3 Supervised and 2 Unsupervised Machine Learning Algorithms to parse through 2 voter files and either predict a vote or generate clusters*

The 3 Supervised algorithms include K-Nearest Neighbor, Perceptron and ID3 Decision Tree. 
The 2 Unsupervised algorithms include K-Means and Agglomerative Clustering (AGNES).

The supervised algorithms were designed **specifically** for the parsing of the voter training data. 
Because there were 9 different attributes and 1 label in the data, the data was simply parsed into different variables.

## Table of Contents
* [Explanation of Algorithms](#explanation)
 * [Supervised Learning](#supervised-learning)
    * [K Nearest Neighbor (KNN)](#knn)
    * [Perceptron](#perceptron)
    * [Decision Tree (ID3)](#id3)
 * [Unsupervised Learning](#unsupervised-learning)
    * [K Means](#kmeans)
    * [Agglomerative Nesting (AGNES)](#agnes)
 * [Additional Information](#additional)
 
##Explanation

###Supervised-Learning

####KNN

The implementation is as follows:
  * The Euclidean distance between a county's data (testing set) and every other county's data (training set) was found
  * The top 10 counties with the smallest Euclidean distance from the inputted county data was retrieved
  * The average of the votes (Democratic/Republican) was then used to predict the vote that the input county would make.
  
The KNN algorithm produced an accuracy rating of *87.96%*
  
####Perceptron

The implementation is as follows:
  * The label value that the Perceptron will produce should be 0 or 1
    * 0 indicating a Republican vote, 1 indicating a Democratic vote
  * Weights for each of the attributes are initialized
    * Since the data was known, very specific weights were used to normalize each attribute
  * Using the training set, the weights were modified to fit the data
    * The difference between the prediction and the actual vote, a specified growth rate and the weight itself were used in this modification
    * If the prediction was too high, it would be lowered. If it was too low, it would be raised.
  * When determining the vote of a testing County data set, it's set of values were dot-producted with the approprates weights and the value was rounded to either 0 or 1 to determine the vote type
  
The Perceptron algorithm produced an accuracy rating of *86.55%*

####ID3

For this algorithm, a specific class called **Node** was made to help build the tree.
The **Node** class held the following information:
  * It's children
  * It's attribute
  * It's minimum bin size, if appropriate

The implementation for the algorithm is as follows:
  * Given a training set, the attribute with the best Gain or the lowest entropy was chosen
  * A node object was initialized with nothing but the best gain attribute
  * This was recursively done until there were no more attributes to pick from. Note that once an attribute was chosen, it could not be chosen again.
  * After the recursive magic was complete, bin values were assigned to nodes that were returned from the recursive call, once again, if appropriate
  * They were then assigned as children to the Node created before the recursive call
  * The tree is now created by the magic of recursion
  * Any county data set would just have to parse the tree with the appropriate attribute until the end of the tree is reached
  * The most common vote of the smaller dataset produced by the tree is the predicted vote of the input county data
  
The ID3 algorithm produced an accuracy rating of *86.59%*

###Unsupervised-Learning

Since unsupervised learning algorithms do not "predict" anything, the silhouette coefficient for the clusterings are used instead to determine the effectiveness of these algorithms. A separate class was made to do this calculation.

####KMeans

The implementation for the algorithm is as follows:
   * The information was initially taken from the information set and parsed into a data structure
   * Since there were only two labels, only 2 clusters were made
   * The centers of these clusters were initalized as random county data values
   * Every county data was then split between these two centers based on the Euclidean distance between itself and the clusters
   * The centers were realligned based on the new clusters
   * And the entire process starts again until no more new centers are made
   * And voila, the clusters are made
   
The Silhouette coefficient for the first cluster was *0.9987* and the Silhouette coefficient for the second cluster was *0.9997*

####AGNES
   
For this algorithm, a specific class called **Unsupervised Node** was made to help build the tree.
The **Unsupervised Node** class held the following information:
   * It's children
   * It's own smaller dataset, if appropriate

The implementation for this algorithm is as follows:
   * Initialize all data entries in the data set as individual clusters
   * Find the two closest clusters using Euclidean distance and combine the clusters into one cluster
   * Do this recursively until there is only one cluster left
   * By the magic of recursion, the Agglomerative Nesting Cluster is made

Since there is only cluster, the silhouette coefficient is *0*.


##Additional

   Outide of the algorithms and classes already described above, there is one additional class made to help with the supervised learning algorithms. In order to keep track of each county, a Data class was made that held each attribute and label for every county. A main class is also included to test each algorithm. Note that the data sets are very skewed in their data since the majority of the votes were Republican, and thus, may have also skewed the results and the accuracy.
