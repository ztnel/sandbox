package tour

func Pic(dx, dy int) [][]uint8 {
	a := make([][]uint8, dy)
	for y:=0; y < dy; y++ {
		for x:=0; x < dx; x++ {
			v := uint8((x * y))
			a[y] = append(a[y], v)
		}
	}
	return a
}
