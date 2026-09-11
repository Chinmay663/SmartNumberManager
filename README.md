Smart Contact Manager

A C++17 command-line application for managing and searching contact information with fast phone-number lookup, prefix-based name search, contact deletion, undo functionality, alphabetical sorting, and persistent CSV storage.

The application maintains in-memory indexes for efficient searching while keeping contact data persisted locally between sessions.

Features
Add Contact — Create and store a new contact with name, phone number, and email.
Phone Search — Find contacts using their phone number.
Prefix Name Search — Search contacts using the beginning of a name.
Delete Contact — Remove a contact using its Contact ID.
Undo — Revert the most recent contact addition or deletion.
Alphabetical Sorting — Sort contacts by name.
Input Validation — Validate contact information before storing it.
Persistent Storage — Store contacts in a CSV file so data remains available across application sessions.
How It Works

The application uses different data structures for different operations.

Contact Storage

Contacts are maintained in memory and persisted to:

data/contacts.csv

When the application starts, existing contacts are loaded from the CSV file. Changes made during the session are written back to the file.

Fast Phone Lookup

Phone numbers are indexed using an unordered_map.

This provides average O(1) phone-number lookup.

Prefix Name Search

Names are stored in a Trie to support prefix-based searching.

For example, searching for:

"jo"

can return contacts such as:

John
Joseph
Jordan

The Trie organizes names character by character and allows the application to retrieve contacts matching a given prefix.

Undo System

Contact modifications are stored using a stack.

The stack follows LIFO (Last In, First Out) behavior, allowing the most recent operation to be undone first.

Alphabetical Sorting

Contacts can be sorted alphabetically by name using Merge Sort, providing O(N log N) sorting complexity.

Architecture

The project separates responsibilities across multiple components:

Component	Responsibility
Contact	Represents contact information
ContactManager	Coordinates contact operations and indexes
FileManager	Handles CSV persistence
Trie	Provides prefix-based name searching
UndoManager	Manages reversible operations
Validator	Validates user input
main.cpp	Handles the application menu and user interaction

This separation keeps contact management, searching, validation, persistence, and user interaction organized into separate components.

Technologies
C++17
CMake
STL
unordered_map
stack
vector
Regular Expressions
File I/O
Trie
Merge Sort
Complexity
Operation	Implementation	Complexity
Phone number search	unordered_map	O(1) average
Prefix search	Trie + DFS	O(P + K)
Alphabetical sorting	Merge Sort	O(N log N)
Add contact	Contact/index update	O(N)
Delete contact	Contact/index update	O(N)
Undo	Stack + contact lookup	O(N)

Where:

N = number of contacts
P = length of the searched prefix
K = number of matching contacts
Building the Application
Requirements
C++17-compatible compiler
CMake 3.10 or later
Build

From the project root:

cmake -S . -B build
cmake --build build

The executable will be generated inside the build directory.

Run

Run the generated SmartContactManager executable.

On Windows, this will be an .exe file.

Example Usage
Main Menu
=== SMART CONTACT MANAGER ===

1. Add Contact
2. Search by Phone
3. Prefix Name Search (Trie)
4. Delete Contact
5. Undo Last Action
6. Sort Alphabetically (Merge Sort)
7. Exit
   
Enter choice:
Adding a Contact
Name: John Doe
Phone: 9876543210
Email: john@example.com

Contact added successfully.
Phone Search
Enter Phone: 9876543210

Found: John Doe
Email: john@example.com
Prefix Search
Enter name prefix: jo

Matching contacts:
John Doe
Joseph Smith
Jordan Lee
Undo
Enter choice: 5

Last action undone successfully.
Design Decisions
Trie for Prefix Search

A Trie is used instead of scanning every contact name because the application needs to support prefix-based searches.

The structure allows the search to navigate directly to the node representing the requested prefix and then retrieve matching names.

unordered_map for Phone Search

Phone numbers provide a natural unique lookup key. An unordered_map allows direct average O(1) access without scanning the entire contact list.

Stack for Undo

Undo operations follow LIFO behavior. The most recent modification must be reversed first, making a stack a natural choice for the undo system.

CSV for Persistence

CSV provides a lightweight, human-readable storage format while avoiding the need for an external database.

Future Improvements
Edit existing contacts
Redo functionality
Multiple-level undo/redo
More efficient incremental index updates
Case-insensitive searching
Improved CSV parsing
Unit and integration tests
Database-backed persistence
Graphical user interface


Author
Built as a portfolio project to demonstrates practical use of data structures and algorithms.
