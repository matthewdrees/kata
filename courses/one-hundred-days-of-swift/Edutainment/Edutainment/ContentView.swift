//
//  ContentView.swift
//  Edutainment
//
//  Created by Matthew Drees on 9/12/23.
//

import SwiftUI

struct Question {
    var n1 : Int
    var n2 : Int
    var ans : Int
}

func generateQuestion(_ maxNum : Int) -> Question {
    let n1 = Int.random(in: 2 ... maxNum)
    let n2 = Int.random(in: 2 ... maxNum)
    return Question(n1: n1, n2:n2, ans: n1 * n2)
}

enum NumQuestionOptions : Int, Identifiable {
    case five = 5
    case ten = 10
    case twenty = 20
    var id: Self { self }
}

struct ContentView: View {
    @State private var showingScore = false
    @State private var scoreTitle = ""

    @State private var numQuestionsSelection : NumQuestionOptions = NumQuestionOptions.five

    private var numQuestions : Int {
        return numQuestionsSelection.rawValue
    }
    @State private var numbersUpTo = 12
    @State private var numQuestionsAsked = 0
    @State private var numQuestionsCorrect = 0
    @State private var question : Question = generateQuestion(12)

    @State private var answer = 0
    @FocusState private var inputIsFocused : Bool


    var body: some View {
        NavigationStack {
            Form {
                Section {
                    Picker("Number of questions", selection: $numQuestionsSelection) {
                        Text("5").tag(NumQuestionOptions.five)
                        Text("10").tag(NumQuestionOptions.ten)
                        Text("20").tag(NumQuestionOptions.twenty)
                    }
                    Stepper(value: $numbersUpTo, in: 2...12, step: 1) {
                        Text("Numbers up to \(numbersUpTo)")
                    }
                }

                Section {
                    Text("\(question.n1) x \(question.n2)")
                    TextField("Answer", value: $answer, format: .number)
                        .keyboardType(.numberPad)
                        .focused($inputIsFocused)
                        .onSubmit {
                            answerSubmitted()
                        }
                }

                Section {
                    Text("\(numQuestionsCorrect)/\(numQuestionsAsked) correct")
                        .frame(maxWidth: .infinity, alignment: .center)
                }
            }
            .navigationTitle("Edutainment")
            .alert(scoreTitle, isPresented: $showingScore) {
                Button("Continue", action: nextQuestion)
            } message: {
                Text("")
            }
            .toolbar {
                ToolbarItemGroup(placement: .keyboard) {
                    Spacer()
                    Button("Done") {
                        inputIsFocused = false
                        answerSubmitted()
                    }
                }
            }
        }
    }

    func answerSubmitted() {
        if answer == question.ans {
            numQuestionsCorrect += 1
            scoreTitle = "Correct, nice work!"
        }
        else {
            scoreTitle = "Wrong! Expected \(question.ans)"
        }
        numQuestionsAsked += 1
        if numQuestionsAsked >= numQuestions {
            numQuestionsAsked = 0
            numQuestionsCorrect = 0
        }
        showingScore = true
    }

    func nextQuestion() {
        self.question = generateQuestion(self.numbersUpTo)
        self.answer = 0

    }
}

//struct ContentView_Previews: PreviewProvider {
//    static var previews: some View {
//        ContentView()
//    }
//}
