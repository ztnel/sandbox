
package tour

import "io"

type InfiniteReader struct { }

func (ir *InfiniteReader) Read(b []byte) (n int, err error) {
    for {
        b = append(b, 'A')
    }
    return n, nil
}

type rot13Reader struct {
	r io.Reader
}

func (rot13 *rot13Reader) Read(b []byte) (n int, err error) {
    n, err = rot13.r.Read(b)
    for i := 0; i < n; i++ {
        if b[i] >= 'A' && b[i] <= 'Z' {
            b[i] = (b[i]-'A'+13)%26 + 'A'
        } else if b[i] >= 'a' && b[i] <= 'z' {
            b[i] = (b[i]-'a'+13)%26 + 'a'
        }
    }
    return n, err
}
