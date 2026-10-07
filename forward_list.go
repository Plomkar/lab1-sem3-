package main

import "fmt"

type FNode struct {
	data string
	next *FNode
}

type FList struct {
	name    string
	head    *FNode
	created bool
}

func NewFList() *FList {
	return &FList{}
}

func (f *FList) Create(name string) bool {
	if name == "" {
		fmt.Println("ERROR: list name is required")
		return false
	}
	f.name = name
	f.created = true
	f.head = nil
	return true
}

func (f *FList) check() bool {
	if !f.created || f.name == "" {
		fmt.Println("ERROR: list name is required")
		return false
	}
	return true
}

func (f *FList) Push(value string) {
	if !f.check() {
		return
	}
	f.head = &FNode{data: value, next: f.head}
}

func (f *FList) PushEnd(value string) {
	if !f.check() {
		return
	}
	newNode := &FNode{data: value}
	if f.head == nil {
		f.head = newNode
		return
	}
	cur := f.head
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = newNode
}

func (f *FList) PushBefore(anchor, value string) {
	if !f.check() {
		return
	}
	if f.head == nil {
		return
	}
	if f.head.data == anchor {
		f.head = &FNode{data: value, next: f.head}
		return
	}
	cur := f.head
	for cur.next != nil && cur.next.data != anchor {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	cur.next = &FNode{data: value, next: cur.next}
}

func (f *FList) PushAfter(anchor, value string) {
	if !f.check() {
		return
	}
	cur := f.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	cur.next = &FNode{data: value, next: cur.next}
}

func (f *FList) Del(anchor string) {
	if !f.check() {
		return
	}
	if f.head == nil {
		return
	}
	if f.head.data == anchor {
		f.head = f.head.next
		return
	}
	cur := f.head
	for cur.next != nil && cur.next.data != anchor {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	cur.next = cur.next.next
}

func (f *FList) DelValue(value string) {
	if !f.check() {
		return
	}
	if f.head == nil {
		return
	}
	if f.head.data == value {
		f.head = f.head.next
		return
	}
	cur := f.head
	for cur.next != nil && cur.next.data != value {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("ERROR: value not found")
		return
	}
	cur.next = cur.next.next
}

func (f *FList) DelBefore(anchor string) {
	if !f.check() {
		return
	}
	if f.head == nil || f.head.data == anchor {
		fmt.Println("ERROR: no element before anchor")
		return
	}
	cur := f.head
	for cur.next != nil && cur.next.data != anchor {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("ERROR: anchor not found")
		return
	}
	cur.next = cur.next.next
}

func (f *FList) DelAfter(anchor string) {
	if !f.check() {
		return
	}
	cur := f.head
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
	cur.next = cur.next.next
}

func (f *FList) Get(anchor string) string {
	if !f.check() {
		return ""
	}
	cur := f.head
	for cur != nil && cur.data != anchor {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("ERROR: anchor not found")
		return ""
	}
	return cur.data
}

func (f *FList) Search(value string) int {
	if !f.check() {
		return -1
	}
	cur := f.head
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

func (f *FList) Print() {
	if !f.check() {
		return
	}
	fmt.Printf("%s: ", f.name)
	cur := f.head
	for cur != nil {
		fmt.Printf("%s ", cur.data)
		cur = cur.next
	}
	fmt.Println()
}
