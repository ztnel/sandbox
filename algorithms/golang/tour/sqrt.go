
package tour

import "math"

func Sqrt(x float64) float64 {
    z := 1.0
    tmp := 0.0
    for math.Abs(z - tmp) > 0 {
        tmp = z
        z = z - (z*z - x) / (2*z)
    }
    return z
}

