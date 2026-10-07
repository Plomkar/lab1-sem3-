package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Storage struct {
	Array *Array
	FList *FList
	LList *LList
	Stack *Stack
	Queue *Queue
}

func NewStorage() *Storage {
	return &Storage{
		Array: NewArray(),
		FList: NewFList(),
		LList: NewLList(),
		Stack: NewStack(),
		Queue: NewQueue(),
	}
}

func (s *Storage) SaveToFile(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	w := bufio.NewWriter(file)
	defer w.Flush()

	fmt.Fprint(w, "M")
	for i := 0; i < s.Array.size; i++ {
		fmt.Fprintf(w, " %s", s.Array.data[i])
	}
	fmt.Fprintln(w)

	fmt.Fprintf(w, "F %s", s.FList.name)
	cur := s.FList.head
	for cur != nil {
		fmt.Fprintf(w, " %s", cur.data)
		cur = cur.next
	}
	fmt.Fprintln(w)

	fmt.Fprintf(w, "L %s", s.LList.name)
	lcur := s.LList.head
	for lcur != nil {
		fmt.Fprintf(w, " %s", lcur.data)
		lcur = lcur.next
	}
	fmt.Fprintln(w)

	fmt.Fprint(w, "S")
	var stackBuf []string
	scur := s.Stack.head
	for scur != nil {
		stackBuf = append(stackBuf, scur.data)
		scur = scur.next
	}
	for i := len(stackBuf) - 1; i >= 0; i-- {
		fmt.Fprintf(w, " %s", stackBuf[i])
	}
	fmt.Fprintln(w)

	fmt.Fprint(w, "Q")
	qcur := s.Queue.head
	for qcur != nil {
		fmt.Fprintf(w, " %s", qcur.data)
		qcur = qcur.next
	}
	fmt.Fprintln(w)

	return nil
}

func (s *Storage) LoadFromFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		if os.IsNotExist(err) {
			return nil
		}
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		if len(parts) < 1 {
			continue
		}
		typeChar := parts[0]

		if typeChar == "F" {
			if len(parts) >= 2 {
				s.FList.Create(parts[1])
				for _, p := range parts[2:] {
					s.FList.PushEnd(p)
				}
			}
		} else if typeChar == "L" {
			if len(parts) >= 2 {
				s.LList.Create(parts[1])
				for _, p := range parts[2:] {
					s.LList.PushEnd(p)
				}
			}
		} else {
			for _, p := range parts[1:] {
				switch typeChar {
				case "M":
					s.Array.Push(p)
				case "S":
					s.Stack.Push(p)
				case "Q":
					s.Queue.Push(p)
				}
			}
		}
	}
	return scanner.Err()
}
