package warmup

import "testing"

type ApplesAndOrangesInput struct {
    s int32
    t int32
    a int32
    b int32
    apples []int32
    oranges []int32
}

type ApplesAndOrangesOutput struct {
    numApples int32
    numOranges int32
}

type ApplesAndOrangesTestCase struct {
    input ApplesAndOrangesInput
    expected ApplesAndOrangesOutput
}

func TestApplesAndOranges(t *testing.T) {
    var testCases = []ApplesAndOrangesTestCase{
        {
            input: ApplesAndOrangesInput{
                s: 7,
                t: 11,
                a: 5,
                b: 15,
                apples: []int32{-2, 2, 1},
                oranges: []int32{5, -6},
            },
            expected: ApplesAndOrangesOutput{
                numApples: 1,
                numOranges: 1,
            },
        },
    }

    for _, test := range testCases {
        result := CountApplesAndOranges(test.input.s, test.input.t, test.input.a, test.input.b, test.input.apples, test.input.oranges)
        if result[0] != test.expected.numApples || result[1] != test.expected.numOranges {
            t.Errorf("Test failed: %v input, %v expected, received: %v", test.input, test.expected, result)
        }
    }
}
