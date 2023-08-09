//
//  ContentView.swift
//  RockPaperScissors
//
//  Created by Matthew Drees on 8/8/23.
//

import SwiftUI


struct ContentView: View {
    let items = ["rock", "paper", "scissors"]
    @State private var doWin : Bool = false
    @State private var appItemIndex = Int.random(in:0...2)
    @State private var showingResult = false
    @State private var scoreTitle = ""
    @State private var score = 0
    let maxAttempts = 10
    @State private var attempts = 0

    var body: some View {

        VStack {
            Text("Rock, Paper, Scissors")
                .font(.largeTitle)
            Spacer()
            Text("Opponent choses:")
            Section {
                Image(items[appItemIndex])
                    .shadow(radius:5)
            }
            Spacer()
            Text("Play to \(doWin ? "win" : "lose"):")
            HStack {
                ForEach(0..<3) { number in
                    Button {
                        itemTapped(number)
                    } label: {
                        Image(items[number])
                            .shadow(radius: 5)
                    }
                    .padding()
                }
            }
            Spacer()
            Text("Score \(score)/\(attempts)")
            Spacer()
        }
        .alert(scoreTitle, isPresented: $showingResult) {
            Button("Continue", action: anotherRound)
        } message: {
            Text("Your score is \(score) out of \(attempts)")
        }

    }
    func itemTapped(_ number: Int) {
        let correct = (appItemIndex + (doWin ? 1: 2)) % 3 == number

        if correct {
            score += 1
            scoreTitle = "Correct, \(items[number]) \(doWin ? "beats" : "loses to") \(items[appItemIndex])"

        }
        else {
            scoreTitle = "Wrong, \(items[number]) does not \(doWin ? "beat" : "lose to") \(items[appItemIndex])"
        }

        doWin.toggle()
        attempts += 1
        showingResult = true
    }
    func anotherRound() {
        if attempts == maxAttempts {
            score = 0
            attempts = 0
        }
        appItemIndex = Int.random(in: 0...2)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
