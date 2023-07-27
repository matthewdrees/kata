//
//  ContentView.swift
//  LengthConversion - Day 19 challenge for 100 days of SwiftUI.
//
//  Created by Matthew Drees on 7/26/23.
//

import SwiftUI


struct ContentView: View {

    enum LengthUnits: String, CaseIterable, Identifiable {
        case Meters, Feet, Kilometers
        var id: Self { self }
    }

    @State private var inLengthUnit: LengthUnits = .Meters
    @State private var outLengthUnit: LengthUnits = .Feet
    @State private var inValue: Double = 0
    @FocusState private var inputIsFocused: Bool

    var outValue : Double {
        var meters = 0.0
        switch inLengthUnit {
        case LengthUnits.Meters:
            meters = inValue
        case LengthUnits.Feet:
            meters = inValue * 0.3048
        case LengthUnits.Kilometers:
            meters = inValue * 1000
        }

        switch outLengthUnit {
        case LengthUnits.Meters:
            return meters
        case LengthUnits.Feet:
            return meters * 3.2808399
        case LengthUnits.Kilometers:
            return meters * 0.001
        }
    }
    var body: some View {
        NavigationStack {
            Form {
                Section {
                    Picker("From", selection: $inLengthUnit) {
                        ForEach(LengthUnits.allCases) {
                            Text($0.rawValue)
                        }
                    }
                    TextField("Input value", value: $inValue, format: .number)
                        .keyboardType(.decimalPad)
                        .focused($inputIsFocused)
                }

                Section {
                    Picker("To", selection: $outLengthUnit) {
                        ForEach(LengthUnits.allCases) {
                            Text($0.rawValue)
                        }
                    }
                    Text(String(format: "%g", outValue))
                }
            }
            .navigationTitle("Length Conversion")
            .toolbar {
                ToolbarItemGroup(placement: .keyboard) {
                    Spacer()
                    Button("Done") {
                        inputIsFocused = false
                    }
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
