package warmup

func GradingStudents(grades []int32) []int32 {
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

