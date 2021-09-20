# Lesson 2 Notes

# Lesson 2 Questionnaire

1. Can we always use a random sample for a validation set? Why or why not?
Not always. The data may trend over time, so you might want to use the more recent data for validation.

2. What is overfitting? Provide an example.
The model can predict validation data at a good rate but does a poorer job of predicting data it hasn't seen yet. An example would be matching specific cats in the validation data but not matching other cats in test data. Another example would be fitting a squigly line to get exact data when a more general line is appropriate.

3. What is a metric? How does it differ from "loss"?
A metric is a function that measures the quality of a model. Examples are error rate and accuracy. These are specific measures of loss. Loss is what the model uses to update its parameters. It is closely related but not quite the same. The example given is you may change parameters in such a small way that the loss changes a little bit but the error rates/accuracy don't change.

4. How can pretrained models help?
Pretrained models save you time. You start with a pretrained model that is known to be useful and refine the training with your data.

5. What is the "head" of a model?
The newly added part of the model that is specific to the new dataset.

6. What kinds of features do the early layers of a CNN find? How about the later layers?
Early layers find things like edges, shapes, simple patterns. Later layers look for higher-level concepts.

7. Are image models only useful for photos?
No. There are several interesting examples where image models are applied to other applications such as sound and malware detection.

8. What is an "architecture"?
Type of model.

9. What is segmentation?
A segmentation model can recognize the content of every pixel in an image.

10. What is y_range used for? When do we need it?
It tells the model that is predicting a number what the range of outputs should be.

11. What are "hyperparameters"?
Higher-level parameters.

12. What's the best way to avoid failures when using AI in an organization?
Set aside test data to verify the effectiveness.

13. What is a p value?
14. What is a prior?
15. Provide an example of where the bear classification model might work poorly in production, due to structural or style differences in the training data.
16. Where do text models currently have a major deficiency?
17. What are possible negative societal implications of text generation models?
18. In situations where a model might make mistakes, and those mistakes could be harmful, what is a good alternative to automating a process?
19. What kind of tabular data is deep learning particularly good at?
20. What's a key downside of directly using a deep learning model for recommendation systems?
21. What are the steps of the Drivetrain Approach?
22. How do the steps of the Drivetrain Approach map to a recommendation system?
23. Create an image recognition model using data you curate, and deploy it on the web.
24. What is DataLoaders?
25. What four things do we need to tell fastai to create DataLoaders?
26. What does the splitter parameter to DataBlock do?
27. How do we ensure a random split always gives the same validation set?
