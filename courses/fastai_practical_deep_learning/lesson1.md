# Lesson 1 Notes
* Regarding notebooks on google colab:
  * Notebook settings do not use GPU hardware by default. Edit -> Notebook settings -> Hardware accelerator.
  * The free account with GPU was a bit slower than my personal computer with no GPU for the first model telling cats from dogs. You get what you pay for.


# Lesson 1 Questionnaire.

1. Do you need these for deep learning?
   * Lots of math. False
   * Lots of data. False
   * Lots of expensive computers. False
   * A PhD. False

2. Name five areas where deep learning is now the best in the world:
Speech recognition, computer vision, classifying proteins in biology, removing noise from images, playing games better than humans.

3. What was the name of the first device that was based on the principle of the artificial neuron?
Mark 1 perceptron.

4. Based on the book of the same name, what are the requirements for parallel distributed processing (PDP)?
Processing units, state of activation, output function, pattern of connectivity, propagation rule, activation rule, learning rule, environment. (Don't know what that stuff means yet though.)

5. What were the two theoretical misunderstandings that held back the field of neural networks?
A single layer of neurons is unable to learn simple functions, and to get good practical performance you need more layers of neurons.

6. What is a GPU?
Graphical Processing Unit.

7. Open a notebook and execute a cell containing: 1+1. What happens?
Outputs 2!

8. Follow through each cell of the stripped version of the notebook for this chapter. Before executing each cell, guess what will happen.

9. Complete the Jupyter Notebook online appendix.

10. Why is it hard to use a traditional computer program to recognize images in a photo?
Computers are "big morons". It's too hard to tell the computer what to do in painstaking enough detail.

11. What did Samuel mean by "weight assignment"?
Adjust parameters of the model.

12. What term do we normally use in deep learning for what Samuel called "weights"?
Parameters.

13. Draw a picture that summarizes Samuel's view of a machine learning model.

   inputs -> model -> results -> performance
               ^                      |
               |          (update)    |
            weights <-----------------+

14. Why is it hard to understand why a deep learning model makes a particular prediction?
If the model is a bunch of "weights" it might not be obvious what real-world meaning each weight has.
Therefore you don't know why the model is the way it is.

15. What is the name of the theorem that shows that a neural network can solve any mathematical problem to any level of accuracy?
Universal approximation theorem. (Very cool.)

16. What do you need in order to train a model?
Input data & labels.

17. How could a feedback loop impact the rollout of a predictive policing model?
The example given was a positive feedback loop that reinforces bad policing biases. (Arresting minority groups more often.)

18. Do we always have to use 224×224-pixel images with the cat recognition model?
No you can pass any size. "If you increase the size, you'll often get a model with better results."

19. What is the difference between classification and regression?
Classification predicts what a thing might be from different categories like "dog" or "cat".
Regression tries to predict numeric qualities like "temperature or location".

20. What is a validation set? What is a test set? Why do we need them?
A validation set is data that is kept separate from the training data to validate the model.
Test data is also kept separate and is another level of sanity check. The author suggests that companies who hire
out AI work keep test data completely separate from the 3rd party to verify their work.

21. What will fastai do if you don't provide a validation set?
Default value is to use 20% of the data for validation.
