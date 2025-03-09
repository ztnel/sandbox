package tour


type Tree struct {
    Left  *Tree
    Value int
    Right *Tree
}

// New returns a new tree with the given value.
func newTree(k int) *Tree {
    // create a random binary tree of size k
    if k == 0 {
        return nil
    }
    return &Tree{newTree(k-1), k, newTree(k-1)}
}

func walk(t *Tree, ch chan int) {
    if t == nil {
        return
    }
    walk(t.Left, ch)
    ch <- t.Value
    walk(t.Right, ch)
}

func walking(t *Tree, ch chan int) {
    walk(t, ch)
    defer close(ch)
}

func same(t1, t2 *Tree) bool {
    if t1 == nil && t2 == nil {
        return true
    }
    if t1 == nil || t2 == nil {
        return false
    }

    ch1, ch2 := make(chan int, 10), make(chan int, 10)
    go walking(t1, ch1)
    go walking(t2, ch2)

    for {
        // get the values from the channels
        v1, ok1 := <-ch1
        v2, ok2 := <-ch2
        // node counts are different
        if ok1 != ok2 {
            return false
        }
        if v1 != v2 {
            return false
        }
        if !ok1 {
            break
        }
    }
    return true
}

func EquivalentBinaryTrees() bool {
    t1 := newTree(2)
    t2 := newTree(2)
    return same(t1, t2)
}
