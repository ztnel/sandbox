package warmup

func CountApplesAndOranges(s int32, t int32, a int32, b int32, apples []int32, oranges []int32) []int32 {
    var counts []int32 = make([]int32, 2)
    for _, apple := range apples {
        apple += a
        if (apple >= s && apple <= t) {
            counts[0]++ 
        }
    }
    for _, orange := range oranges {
        orange += b
        if (orange >= s && orange <= t) {
            counts[1]++ 
        }
    }
    return counts
}

