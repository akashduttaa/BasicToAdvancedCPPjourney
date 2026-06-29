import json
import datetime
import os

# ---FEATURE: Colored Terminal Output ---
class Color:
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    CYAN = '\033[96m'
    RESET = '\033[0m'

class Student:
    def __init__(self, roll, name, age, branch, marks, attendance):
        self.roll = roll
        self.name = name
        self.age = age
        self.branch = branch
        self.marks = marks
        self.attendance = attendance

    # ---FEATURE: Percentage & Grade System ---
    def get_percentage(self):
        if not self.marks: return 0.0
        return sum(self.marks) / len(self.marks)

    def calculate_grade(self):
        avg = self.get_percentage()
        if avg >= 90: return 'O'
        elif avg >= 80: return 'E'
        elif avg >= 70: return 'A'
        elif avg >= 60: return 'B'
        else: return 'F'

    # Helper for JSON saving
    def to_dict(self):
        return {"roll": self.roll, "name": self.name, "age": self.age, 
                "branch": self.branch, "marks": self.marks, "attendance": self.attendance}

class StudentManagement:
    def __init__(self):
        self.students = {}  
        self.subjects = ("Python", "DSA", "Mathematics") 
        self.active_branches = set()
        self.filename = "student_database.json"

    # --- FEATURE: Password Login ---
    def login(self):
        print(Color.CYAN + "\n🔒 SECURE SYSTEM LOGIN" + Color.RESET)
        while True:
            pwd = input("Enter Admin Password (hint: root): ")
            if pwd == "root":
                print(Color.GREEN + "✅ Access Granted!\n" + Color.RESET)
                break
            else:
                print(Color.RED + "❌ Access Denied. Try again." + Color.RESET)

    # --- FEATURE: Load from File ---
    def load_data(self):
        if os.path.exists(self.filename):
            try:
                with open(self.filename, "r") as file:
                    data = json.load(file)
                    for roll, info in data.items():
                        self.students[roll] = Student(**info)
                        self.active_branches.add(info['branch'])
                print(Color.GREEN + f"✅ Loaded {len(self.students)} records from file." + Color.RESET)
            except Exception as e:
                print(Color.RED + f"Error loading data: {e}" + Color.RESET)
        else:
            print(Color.YELLOW + "⚠️ No existing database found. Starting fresh." + Color.RESET)

    # --- FEATURE: Save to File ---
    def save_data(self):
        data = {roll: student.to_dict() for roll, student in self.students.items()}
        try:
            with open(self.filename, "w") as file:
                json.dump(data, file, indent=4)
            print(Color.GREEN + "✅ All data successfully saved to database!" + Color.RESET)
        except Exception as e:
            print(Color.RED + f"Error saving data: {e}" + Color.RESET)

    def add_student(self):
        print(Color.CYAN + "\n--- Add New Student ---" + Color.RESET)
        roll = input("Enter Roll No: ")
        if roll in self.students:
            print(Color.RED + "Error: Student already exists!" + Color.RESET)
            return
            
        name = input("Enter Name: ").title()
        
        while True:
            try:
                age = int(input("Enter Age: "))
                break
            except ValueError:
                print(Color.RED + "❌ Invalid input! Enter a whole number." + Color.RESET)
                
        branch = input("Enter Branch: ").upper()
        
        marks = []
        print(f"\nEnter marks for {self.subjects}:")
        for sub in self.subjects:
            while True:  
                try:
                    mark = float(input(f"{sub} Marks (0-100): "))
                    if 0 <= mark <= 100:
                        marks.append(mark)
                        break
                    else:
                        print(Color.RED + "❌ Marks must be between 0 and 100." + Color.RESET)
                except ValueError:
                    print(Color.RED + "❌ Invalid input! Enter a number." + Color.RESET)
                    
        while True:
            try:
                attendance = float(input("Enter Attendance %: "))
                if 0 <= attendance <= 100:
                    break
                else:
                    print(Color.RED + "❌ Attendance must be between 0 and 100." + Color.RESET)
            except ValueError:
                print(Color.RED + "❌ Invalid input! Enter a number." + Color.RESET)
        
        self.students[roll] = Student(roll, name, age, branch, marks, attendance)
        self.active_branches.add(branch)
        print(Color.GREEN + "✅ Student added successfully." + Color.RESET)

    # --- FEATURE: Sort Students ---
    def view_students(self):
        print(Color.CYAN + "\n--- All Student Records (Sorted by Roll) ---" + Color.RESET)
        if not self.students:
            print(Color.YELLOW + "No records found." + Color.RESET)
            return
        
        print(f"{'Roll':<12} | {'Name':<15} | {'Branch':<8} | {'%':<6} | {'Grade':<5} | {'Attendance'}")
        print("-" * 70)
        
        # Sorting dictionary keys alphabetically
        for roll in sorted(self.students.keys()):
            student = self.students[roll]
            pct = student.get_percentage()
            grade = student.calculate_grade()
            print(f"{roll:<12} | {student.name:<15} | {student.branch:<8} | {pct:<6.2f} | {grade:<5} | {student.attendance}%")

    # --- FEATURE: Search by Name ---
    def search_student(self):
        query = input("\nEnter Name to search: ").lower()
        found = False
        print("-" * 70)
        for student in self.students.values():
            if query in student.name.lower():
                pct = student.get_percentage()
                print(f"Found: {student.roll} | {student.name} | {student.branch} | {pct:.2f}% | Grade: {student.calculate_grade()}")
                found = True
        
        if not found:
            print(Color.RED + "❌ No student found with that name." + Color.RESET)

    # --- FEATURE: Highest, Lowest, Average, and Topper ---
    def show_statistics(self):
        print(Color.CYAN + "\n--- Batch Statistics & Leaderboard ---" + Color.RESET)
        if not self.students:
            print(Color.YELLOW + "No data available to calculate stats." + Color.RESET)
            return
            
        all_students = list(self.students.values())
        
        # Calculations
        class_avg = sum(s.get_percentage() for s in all_students) / len(all_students)
        topper = max(all_students, key=lambda s: s.get_percentage())
        lowest = min(all_students, key=lambda s: s.get_percentage())
        
        print(Color.GREEN + f"👑 BATCH TOPPER: {topper.name} ({topper.roll}) with {topper.get_percentage():.2f}%" + Color.RESET)
        print(f"📈 Highest Marks: {topper.get_percentage():.2f}%")
        print(f"📉 Lowest Marks: {lowest.get_percentage():.2f}%")
        print(f"📊 Class Average: {class_avg:.2f}%")
        print(f"🏢 Active Branches: {', '.join(self.active_branches)}")

    # --- FEATURE: Menu-Driven Interface & Date/Time ---
    def run(self):
        self.login()
        self.load_data()
        
        while True:
            now = datetime.datetime.now().strftime("%Y-%m-%d %I:%M %p")
            print(Color.YELLOW + "\n" + "="*45)
            print(f"🏆 SMART STUDENT MANAGEMENT SYSTEM")
            print(f"🕒 {now}")
            print("="*45 + Color.RESET)
            print("1. Add Student")
            print("2. View All Students (Sorted)")
            print("3. Search Student by Name")
            print("4. View Batch Stats & Topper")
            print("5. Save Data to File")
            print("6. Exit")
            
            choice = input("Enter your choice (1-6): ")
            
            if choice == '1': self.add_student()
            elif choice == '2': self.view_students()
            elif choice == '3': self.search_student()
            elif choice == '4': self.show_statistics()
            elif choice == '5': self.save_data()
            elif choice == '6':
                self.save_data() # Auto-save on exit
                print(Color.GREEN + "Goodbye!" + Color.RESET)
                break
            else:
                print(Color.RED + "❌ Invalid choice." + Color.RESET)

if __name__ == "__main__":
    app = StudentManagement()
    
    # Pre-load your dummy data only if the dictionary is empty (meaning no file was loaded)
    if not os.path.exists(app.filename):
        app.students["184"] = Student("184", "Akash Dutta", 22, "CSE", [88.5, 92.0, 85.0], 94.5)
        app.active_branches.add("CSE")
        
    app.run()