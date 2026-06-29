class Student:
    """OOP Concept: Class defining student attributes and behaviors."""
    def __init__(self, roll, name, age, branch, marks, attendance):
        self.roll = roll
        self.name = name
        self.age = age
        self.branch = branch
        self.marks = marks  # List concept: Stores multiple subject marks
        self.attendance = attendance

    def calculate_grade(self):
        """Conditionals concept: Calculates grade based on average marks."""
        if not self.marks: return "N/A"
        avg = sum(self.marks) / len(self.marks)
        
        if avg >= 90: return 'O'
        elif avg >= 80: return 'E'
        elif avg >= 70: return 'A'
        elif avg >= 60: return 'B'
        else: return 'F'

class StudentManagement:
    """OOP Concept: Manager class handling the collection of students."""
    def __init__(self):
        self.students = {}  # Dictionary concept: Maps Roll -> Student Object
        self.subjects = ("Python", "DSA", "Mathematics")  # Tuple concept: Fixed subjects
        self.active_branches = set()  # Set concept: Stores unique branches

    def add_student(self):
        print("\n--- Add New Student ---")
        roll = input("Enter Roll No: ")
        
        # Conditional Concept: Check if key exists in dictionary
        if roll in self.students:
            print("Error: Student already exists!")
            return
            
        name = input("Enter Name: ")
        
        # Exception Handling for Age
        while True:
            try:
                age = int(input("Enter Age: "))
                break
            except ValueError:
                print("❌ Invalid input! Please enter a whole number.")
                
        branch = input("Enter Branch: ")
        
        marks = []
        print(f"\nEnter marks for {len(self.subjects)} subjects {self.subjects}:")
        
        # For Loop Concept: Iterate through the tuple of subjects
        for sub in self.subjects:
            while True:  # Exception Handling for Marks
                try:
                    mark = float(input(f"{sub} Marks: "))
                    if 0 <= mark <= 100:
                        marks.append(mark)
                        break
                    else:
                        print("❌ Marks must be between 0 and 100.")
                except ValueError:
                    print("❌ Invalid input! Please enter a single number (e.g., 95 or 88.5).")
                    
        # Exception Handling for Attendance
        while True:
            try:
                attendance = float(input("Enter Attendance %: "))
                if 0 <= attendance <= 100:
                    break
                else:
                    print("❌ Attendance must be between 0 and 100.")
            except ValueError:
                print("❌ Invalid input! Please enter a number.")
        
        # Storing object in Dictionary and unique branch in Set
        self.students[roll] = Student(roll, name, age, branch, marks, attendance)
        self.active_branches.add(branch)
        print("✅ Student added successfully.")

    def view_students(self):
        print("\n--- All Student Records ---")
        if not self.students:
            print("No records found.")
            return
        
        print(f"{'Roll':<12} | {'Name':<15} | {'Branch':<8} | {'Grade':<5} | {'Attendance'}")
        print("-" * 65)
        
        # For Loop Concept: Iterating over Dictionary keys and values
        for roll, student in self.students.items():
            grade = student.calculate_grade()
            print(f"{roll:<12} | {student.name:<15} | {student.branch:<8} | {grade:<5} | {student.attendance}%")

    def show_statistics(self):
        print("\n--- Batch Statistics ---")
        if not self.students:
            print("No data available.")
            return
            
        # List comprehension to gather all averages
        all_averages = [sum(s.marks)/len(s.marks) for s in self.students.values()]
        
        class_avg = sum(all_averages) / len(all_averages)
        highest = max(all_averages)
        lowest = min(all_averages)
        
        print(f"Class Average Marks: {class_avg:.2f}%")
        print(f"Highest Average: {highest:.2f}%")
        print(f"Lowest Average: {lowest:.2f}%")
        print(f"Active Branches in System: {', '.join(self.active_branches)}")

    def run(self):
        """While loop concept: Keeps the main menu running."""
        while True:
            print("\n" + "="*35)
            print("🏆 SMART STUDENT MANAGEMENT SYSTEM")
            print("="*35)
            print("1. Add Student")
            print("2. View All Students & Grades")
            print("3. View Batch Statistics")
            print("4. Exit System")
            
            choice = input("Enter your choice (1-4): ")
            
            if choice == '1':
                self.add_student()
            elif choice == '2':
                self.view_students()
            elif choice == '3':
                self.show_statistics()
            elif choice == '4':
                print("Saving data and exiting... Goodbye!")
                break
            else:
                print("❌ Invalid choice. Please enter a number between 1 and 4.")

if __name__ == "__main__":
    # Initialize system
    app = StudentManagement()
    
    # Pre-loaded data for demonstration
    app.students["184"] = Student("184", "Akash Dutta", 22, "CSE", [88.5, 92.0, 85.0], 94.5)
    app.active_branches.add("CSE")
    
    # Start the application
    app.run()