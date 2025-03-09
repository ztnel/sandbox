package warmup

import "testing"

type TestCase struct {
    input []int32
    expected []int32
}

func TestGradingStudents(t *testing.T) {
    var testCases = []TestCase{
        {
            input: []int32{73, 67, 38, 33},
            expected: []int32{75, 67, 40, 33},
        },
        {
            input: []int32{84, 56, 32, 99},
            expected: []int32{85, 56, 32, 100},
        },
    }

    for _, test := range testCases {
        result := GradingStudents(test.input)
        for i, grade := range result {
            if !(grade == test.expected[i]) {
                t.Errorf("Test failed: %v input, %v expected, received: %v", test.input, test.expected, result)
            }
        }
    }
}
