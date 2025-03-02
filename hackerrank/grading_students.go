package main

import "fmt"

/*
 * Complete the 'gradingStudents' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY grades as parameter.
 */
func gradingStudents(grades []int32) []int32 {
    for i, grade := range grades {
        if (grade >= 38) {
            var modulo int32 = grade % 5
            if (modulo > 2) {
                grades[i] = grade + 5 - modulo
            }
        }
    }
    return grades
}

func main() {
    // Test case
    grades := []int32{73, 67, 38, 33, 39}
    result := gradingStudents(grades)
    fmt.Println(result)
}
