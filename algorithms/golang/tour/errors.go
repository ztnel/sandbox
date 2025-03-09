package tour

import (
	"fmt"
	"time"
)

// custom error struct that implements the error interface
type MyError struct {
	When time.Time
	What string
}

func (e *MyError) Error() string {
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)
}

type ErrNegativeSqrt float64

func (err ErrNegativeSqrt) Error() string {
    return fmt.Sprintf("cannot sqrt negative number: %v", float64(err))
}

func SqrtError(x float64) (float64, error) {
    if (x < 0) {
        return 0, ErrNegativeSqrt(x)
    }
	return Sqrt(float64(x)), nil
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}

