package main

import "fmt"

type Array struct {
	data     []string
	size     int
	capacity int
}

func NewArray() *Array {
	return &Array{
		data:     make([]string, 4),
		size:     0,
		capacity: 4,
	}
}

func (a *Array) grow() {
	newCap := a.capacity * 2
	newData := make([]string, newCap)
	copy(newData, a.data[:a.size])
	a.data = newData
	a.capacity = newCap
}

func (a *Array) Push(value string) {
	if a.size >= a.capacity {
		a.grow()
	}
	a.data[a.size] = value
	a.size++
}

func (a *Array) PushAt(index int, value string) error {
	if index < 0 || index > a.size {
		return fmt.Errorf("index out of range")
	}
	if a.size >= a.capacity {
		a.grow()
	}
	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.size++
	return nil
}

func (a *Array) Get(index int) (string, error) {
	if index < 0 || index >= a.size {
		return "", fmt.Errorf("index out of range")
	}
	return a.data[index], nil
}

func (a *Array) Del(index int) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range")
	}
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.data[a.size-1] = ""
	a.size--
	return nil
}

func (a *Array) Set(index int, value string) error {
	if index < 0 || index >= a.size {
		return fmt.Errorf("index out of range")
	}
	a.data[index] = value
	return nil
}

func (a *Array) Len() int {
	return a.size
}

func (a *Array) Print() {
	for i := 0; i < a.size; i++ {
		fmt.Printf("%s ", a.data[i])
	}
	fmt.Println()
}
