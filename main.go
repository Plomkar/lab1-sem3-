package main

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var storage = NewStorage()

func processQuery(query string) {
	parts := strings.Fields(query)
	if len(parts) == 0 {
		fmt.Println("Empty query")
		return
	}
	cmd := parts[0]
	args := parts[1:]

	switch cmd {

	case "MPUSH":
		if len(args) == 1 {
			storage.Array.Push(args[0])
			fmt.Println(args[0])
		} else if len(args) == 2 {
			idx, err := strconv.Atoi(args[0])
			if err == nil {
				if err := storage.Array.PushAt(idx, args[1]); err != nil {
					fmt.Println("Error:", err)
				} else {
					fmt.Println(args[1])
				}
			} else {
				storage.Array.Push(args[0])
				fmt.Println(args[0])
			}
		}
	case "MGET":
		if len(args) == 1 {
			idx, _ := strconv.Atoi(args[0])
			v, err := storage.Array.Get(idx)
			if err != nil {
				fmt.Println("Error:", err)
			} else {
				fmt.Println(v)
			}
		}
	case "MDEL":
		if len(args) == 1 {
			idx, _ := strconv.Atoi(args[0])
			if err := storage.Array.Del(idx); err != nil {
				fmt.Println("Error:", err)
			} else {
				fmt.Println("OK")
			}
		}
	case "MSET":
		if len(args) == 2 {
			idx, _ := strconv.Atoi(args[0])
			if err := storage.Array.Set(idx, args[1]); err != nil {
				fmt.Println("Error:", err)
			} else {
				fmt.Println("OK")
			}
		}
	case "MLEN":
		fmt.Println(storage.Array.Len())

	case "FCREATE":
		if len(args) == 1 {
			if storage.FList.Create(args[0]) {
				fmt.Println("OK")
			}
		} else {
			fmt.Println("ERROR: list name is required")
		}
	case "FPUSH":
		if len(args) == 0 {
			fmt.Println("ERROR: list name is required")
		} else if len(args) == 1 {
			storage.FList.Push(args[0])
			fmt.Println("OK")
		} else if len(args) == 2 {
			if args[1] == "END" {
				storage.FList.PushEnd(args[0])
			} else {
				storage.FList.PushBefore(args[1], args[0])
			}
			fmt.Println("OK")
		}
	case "FPUSH_BEFORE":
		if len(args) == 2 {
			storage.FList.PushBefore(args[0], args[1])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor and value required")
		}
	case "FPUSH_AFTER":
		if len(args) == 2 {
			storage.FList.PushAfter(args[0], args[1])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor and value required")
		}
	case "FGET":
		if len(args) == 1 {
			res := storage.FList.Get(args[0])
			if res != "" {
				fmt.Println(res)
			}
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "FDEL":
		if len(args) == 0 {
			fmt.Println("ERROR: anchor required")
		} else if len(args) == 1 {
			storage.FList.Del(args[0])
			fmt.Println("OK")
		} else if len(args) == 2 && args[0] == "VALUE" {
			storage.FList.DelValue(args[1])
			fmt.Println("OK")
		}
	case "FDEL_BEFORE":
		if len(args) == 1 {
			storage.FList.DelBefore(args[0])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "FDEL_AFTER":
		if len(args) == 1 {
			storage.FList.DelAfter(args[0])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "FSEARCH":
		if len(args) == 1 {
			fmt.Println(storage.FList.Search(args[0]))
		} else {
			fmt.Println("ERROR: value required")
		}

	case "LCREATE":
		if len(args) == 1 {
			if storage.LList.Create(args[0]) {
				fmt.Println("OK")
			}
		} else {
			fmt.Println("ERROR: list name is required")
		}
	case "LPUSH":
		if len(args) == 0 {
			fmt.Println("ERROR: list name is required")
		} else if len(args) == 1 {
			storage.LList.Push(args[0])
			fmt.Println("OK")
		} else if len(args) == 2 {
			if args[1] == "END" {
				storage.LList.PushEnd(args[0])
			} else {
				storage.LList.PushBefore(args[1], args[0])
			}
			fmt.Println("OK")
		}
	case "LPUSH_BEFORE":
		if len(args) == 2 {
			storage.LList.PushBefore(args[0], args[1])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor and value required")
		}
	case "LPUSH_AFTER":
		if len(args) == 2 {
			storage.LList.PushAfter(args[0], args[1])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor and value required")
		}
	case "LGET":
		if len(args) == 1 {
			res := storage.LList.Get(args[0])
			if res != "" {
				fmt.Println(res)
			}
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "LDEL":
		if len(args) == 0 {
			fmt.Println("ERROR: anchor required")
		} else if len(args) == 1 {
			storage.LList.Del(args[0])
			fmt.Println("OK")
		} else if len(args) == 2 && args[0] == "VALUE" {
			storage.LList.DelValue(args[1])
			fmt.Println("OK")
		}
	case "LDEL_BEFORE":
		if len(args) == 1 {
			storage.LList.DelBefore(args[0])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "LDEL_AFTER":
		if len(args) == 1 {
			storage.LList.DelAfter(args[0])
			fmt.Println("OK")
		} else {
			fmt.Println("ERROR: anchor required")
		}
	case "LSEARCH":
		if len(args) == 1 {
			fmt.Println(storage.LList.Search(args[0]))
		} else {
			fmt.Println("ERROR: value required")
		}

	case "SPUSH":
		if len(args) == 1 {
			storage.Stack.Push(args[0])
			fmt.Println(args[0])
		}
	case "SPOP":
		fmt.Println(storage.Stack.Pop())
	case "SPEEK":
		fmt.Println(storage.Stack.Peek())

	case "QPUSH":
		if len(args) == 1 {
			storage.Queue.Push(args[0])
			fmt.Println(args[0])
		}
	case "QPOP":
		fmt.Println(storage.Queue.Pop())
	case "QPEEK":
		fmt.Println(storage.Queue.Peek())

	case "PRINT":
		if len(args) == 1 {
			switch args[0] {
			case "M":
				storage.Array.Print()
			case "F":
				storage.FList.Print()
			case "L":
				storage.LList.Print()
			case "S":
				storage.Stack.Print()
			case "Q":
				storage.Queue.Print()
			default:
				fmt.Println("Unknown container:", args[0])
			}
		}
	case "PRINT_REVERSE":
		if len(args) == 1 {
			switch args[0] {
			case "L":
				storage.LList.PrintReverse()
			default:
				fmt.Println("Unknown container:", args[0])
			}
		}

	default:
		fmt.Println("Unknown command:", cmd)
	}
}

func main() {
	filePtr := flag.String("file", "", "data file")
	queryPtr := flag.String("query", "", "query to execute")
	flag.Parse()

	if *filePtr == "" {
		fmt.Println("Usage: ./dbms --file <file.data> --query '<COMMAND> [args]'")
		os.Exit(1)
	}

	if err := storage.LoadFromFile(*filePtr); err != nil {
		fmt.Println("Error loading file:", err)
	}

	if *queryPtr == "" {
		fmt.Println("No query provided")
		os.Exit(0)
	}

	processQuery(*queryPtr)

	if err := storage.SaveToFile(*filePtr); err != nil {
		fmt.Println("Error saving file:", err)
	}
}
