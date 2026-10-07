package main

import "fmt"

type QNode struct {
	data string
	next *QNode
}

type Queue struct {
	head *QNode
	tail *QNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) IsEmpty() bool {
	return q.head == nil
}

func (q *Queue) Push(value string) {
	newNode := &QNode{data: value}
	if q.tail != nil {
		q.tail.next = newNode
	} else {
		q.head = newNode
	}
	q.tail = newNode
}

func (q *Queue) Pop() string {
	if q.IsEmpty() {
		fmt.Println("Queue is empty")
		return ""
	}
	val := q.head.data
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	return val
}

func (q *Queue) Peek() string {
	if q.IsEmpty() {
		return ""
	}
	return q.head.data
}

func (q *Queue) Print() {
	cur := q.head
	for cur != nil {
		fmt.Printf("%s ", cur.data)
		cur = cur.next
	}
	fmt.Println()
}
