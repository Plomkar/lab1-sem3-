package main

import "fmt"

type LNode struct {
	data string
	prev *LNode
	next *LNode
}

type LList struct {
	name    string
	head    *LNode
	tail    *LNode
	created bool
}

func NewLList() *LList {
	return &LList{}
}

func (l *LList) Create(name string) bool {
	if name == "" {
		fmt.Println("ERROR: list name is required")
		return false
	}
	l.name = name
	l.created = true
	l.head = nil
	l.tail = nil
	return true
}

func (l *LList) check() bool {
	if !l.created || l.name == "" {
		fmt.Println("ERROR: list name is required")
		return false
	}
	return true
}

func (l *LList) Push(value string) {
	if !l.check() {
		return
	}
	newNode := &LNode{data: value, next: l.head}
	if l.head != nil {
		l.head.prev = newNode
	} else {
		l.tail = newNode
	}
	l.head = newNode
}

func (l *LList) PushEnd(value string) {
	if !l.check() {
		return
	}
	newNode := &LNode{data: value, prev: l.tail}
	if l.tail != nil {
		l.tail.next = newNode
	} else {
		l.head = newNode
	}
	l.tail = newNode
}

func (l *LList) PushBefore(anchor, value string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	newNode := &LNode{data: value, prev: cur.prev, next: cur}
	if cur.prev != nil {
		cur.prev.next = newNode
	} else {
		l.head = newNode
	}
	cur.prev = newNode
}

func (l *LList) PushAfter(anchor, value string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	newNode := &LNode{data: value, prev: cur, next: cur.next}
	if cur.next != nil {
		cur.next.prev = newNode
	} else {
		l.tail = newNode
	}
	cur.next = newNode
}

func (l *LList) Del(anchor string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	if cur.prev != nil {
		cur.prev.next = cur.next
	} else {
		l.head = cur.next
	}
	if cur.next != nil {
		cur.next.prev = cur.prev
	} else {
		l.tail = cur.prev
	}
}

func (l *LList) DelValue(value string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != value {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: value not found")
		return
	}
	if cur.prev != nil {
		cur.prev.next = cur.next
	} else {
		l.head = cur.next
	}
	if cur.next != nil {
		cur.next.prev = cur.prev
	} else {
		l.tail = cur.prev
	}
}

func (l *LList) DelBefore(anchor string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	if cur.prev == nil {
		fmt.Println("ERROR: no element before anchor")
		return
	}
	del := cur.prev
	if del.prev != nil {
		del.prev.next = cur
	} else {
		l.head = cur
	}
	cur.prev = del.prev
}

func (l *LList) DelAfter(anchor string) {
	if !l.check() {
		return
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	if cur.next == nil {
		fmt.Println("ERROR: no element after anchor")
		return
	}
	del := cur.next
	cur.next = del.next
	if del.next != nil {
		del.next.prev = cur
	} else {
		l.tail = cur
	}
}

func (l *LList) Get(anchor string) string {
	if !l.check() {
		return ""
	}
	cur := l.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return ""
	}
	return cur.data
}

func (l *LList) Search(value string) int {
	if !l.check() {
		return -1
	}
	cur := l.head
	idx := 0
	for cur != nil {
		if cur.data == value {
			return idx
		}
		cur = cur.next
		idx++
	}
	return -1
}

func (l *LList) Print() {
	if !l.check() {
		return
	}
	fmt.Printf("%s: ", l.name)
	cur := l.head
	for cur != nil {
		fmt.Printf("%s ", cur.data)
		cur = cur.next
	}
	fmt.Println()
}

func (l *LList) PrintReverse() {
	if !l.check() {
		return
	}
	fmt.Printf("%s (reverse): ", l.name)
	cur := l.tail
	for cur != nil {
		fmt.Printf("%s ", cur.data)
		cur = cur.prev
	}
	fmt.Println()
}
