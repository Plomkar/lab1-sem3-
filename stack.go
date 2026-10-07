package main

import "fmt"

type SNode struct {
	data string
	next *SNode
}

type Stack struct {
	head *SNode
}

func NewStack() *Stack {
	return &Stack{}
}

func (s *Stack) IsEmpty() bool {
	return s.head == nil
}

func (s *Stack) Push(value string) {
	s.head = &SNode{data: value, next: s.head}
}

func (s *Stack) Pop() string {
	if s.IsEmpty() {
		fmt.Println("Stack is empty")
		return ""
	}
	val := s.head.data
	s.head = s.head.next
	return val
}

func (s *Stack) Peek() string {
	if s.IsEmpty() {
		return ""
	}
	return s.head.data
}

func (s *Stack) Print() {
	cur := s.head
	for cur != nil {
		fmt.Printf("%s ", cur.data)
		cur = cur.next
	}
	fmt.Println()
}
