# Lesson 2 Notes
* Good bing API search tutorial here: https://docs.microsoft.com/en-us/bing/search-apis/bing-web-search/search-the-web

# Lesson 2 Questionnaire

1. Can we always use a random sample for a validation set? Why or why not?
Not always. The data may trend over time, so you might want to use the more recent data for validation.

2. What is overfitting? Provide an example.
The model can predict validation data at a good rate but does a poorer job of predicting data it hasn't seen yet. An example would be matching specific cats in the validation data but not matching other cats in test data. Another example would be fitting a squiggly line to get exact data when a more general line is appropriate.

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
The probability of an observed result assuming that the null hypothesis is true. Ha! "They are almost always Terrible." It doesn't measure the importance of a result. It does not provide a good measure of evidence. Quotes Frank Harrell.

14. What is a prior?
Got this from Wikipedia... the probability about one's beliefs before evidence is taken into account.

15. Provide an example of where the bear classification model might work poorly in production, due to structural or style differences in the training data.

16. Where do text models currently have a major deficiency?
Text models are great at *sounding* good, but might not actually be right.

17. What are possible negative societal implications of text generation models?
Because they *sound* good they can be effective at "spread misinformation, create unrest, and encourage conflict".

18. In situations where a model might make mistakes, and those mistakes could be harmful, what is a good alternative to automating a process?
Run a manual process, and run the model in parallel. Then do a "Limited scope deployment" with the model carefully supervised by people.

19. What kind of tabular data is deep learning particularly good at?
Deep learning increases the variety of columns you include. The examples given are columns with natural language and columns with "high-cardinality" such as zip codes.

20. What's a key downside of directly using a deep learning model for recommendation systems?
In the case of books, it will likely recommend other books by the same author, rather than a recommendation a book store employee or librarian might give you.

21. What are the steps of the Drivetrain Approach?
* Define Objective. What is the user's main objective?
* Levers. What actions can you take to better achieve the objective?
* Data.
* Models.

22. How do the steps of the Drivetrain Approach map to a recommendation system?
The example given says:
* Define Objective: "Drive additional sales by surprising and delighting the customer with recommendations of items they would not have purchased without the recommendation."
* Levers: "Ranking of recommendations"
* Data: Randomized experiments to collect customer data.
* Models: Could build two models for purchase probabilities, conditional on seeing or not seeing a recommendation."

23. Create an image recognition model using data you curate, and deploy it on the web.
Sigh. Fine.

24. What is DataLoaders?
A thin wrapper class that holds DataLoader objects, which make data available as training or validating data.

25. What four things do we need to tell fastai to create DataLoaders?
* What kind of data we are working with
* How to get the list of items
* How to label these items
* How to create the validation set

26. What does the splitter parameter to DataBlock do?
How to split the data into training and validation.

27. How do we ensure a random split always gives the same validation set?
Use the same seed.
