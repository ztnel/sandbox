
package tour

// List represents a singly-linked list that holds
// values of any type.
type List[T any] struct {
	next *List[T]
	val  T
}

func LinkedListCreate(size int) *List[int] {
    // Create a linked list.
    l := &List[int]{val: 0}
    for i := 1; i < size; i++ {
        l = &List[int]{val: i, next: l}
    }
    return l
}
