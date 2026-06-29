import json
import datetime
import os

# --- ANSI Colors for Terminal ---
class Color:
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    CYAN = '\033[96m'
    MAGENTA = '\033[95m'
    RESET = '\033[0m'
    BOLD = '\033[1m'

class Book:
    """Class representing an individual book entity."""
    def __init__(self, book_id, title, author, is_issued=False, issued_to=""):
        self.book_id = book_id
        self.title = title
        self.author = author
        self.is_issued = is_issued
        self.issued_to = issued_to

    def to_dict(self):
        return {
            "title": self.title,
            "author": self.author,
            "is_issued": self.is_issued,
            "issued_to": self.issued_to
        }

class LibraryManager:
    def __init__(self):
        self.books = {}
        self.filename = "library_data.json"
        self.id_counter = 1001  # Starting point for Auto-generated IDs

    # --- SAVE / LOAD DATA (Exception Handling) ---
    def load_data(self):
        if os.path.exists(self.filename):
            try:
                with open(self.filename, 'r') as f:
                    data = json.load(f)
                    for b_id, info in data.items():
                        self.books[b_id] = Book(b_id, **info)
                        # Ensure auto-id counter stays ahead of existing IDs
                        num = int(b_id[1:])
                        if num >= self.id_counter:
                            self.id_counter = num + 1
                print(Color.GREEN + f"✅ Successfully loaded {len(self.books)} books from database." + Color.RESET)
            except Exception as e:
                print(Color.RED + f"❌ Error loading data: {e}" + Color.RESET)
        else:
            print(Color.YELLOW + "⚠️ No existing database found. Starting fresh." + Color.RESET)

    def save_data(self, auto_save=False):
        try:
            data = {b_id: book.to_dict() for b_id, book in self.books.items()}
            with open(self.filename, 'w') as f:
                json.dump(data, f, indent=4)
            if not auto_save:
                print(Color.GREEN + "💾 ✅ Data successfully saved to JSON file!" + Color.RESET)
        except Exception as e:
            print(Color.RED + f"❌ Error saving data: {e}" + Color.RESET)

    def generate_id(self):
        """Auto-generates sequential Book IDs (e.g., B1001, B1002)"""
        new_id = f"B{self.id_counter}"
        self.id_counter += 1
        return new_id

    # --- MENU 1: BOOK MANAGEMENT ---
    def book_management(self):
        print(Color.CYAN + "\n--- 📚 Book Management ---" + Color.RESET)
        print("1. Add New Book")
        print("2. Delete Book")
        print("3. Back to Main Menu")
        
        choice = input("Select an option: ")
        if choice == '1':
            title = input("Enter Book Title: ").strip().title()
            author = input("Enter Author Name: ").strip().title()
            
            if not title or not author:
                print(Color.RED + "❌ Title and Author cannot be empty!" + Color.RESET)
                return
                
            new_id = self.generate_id()
            self.books[new_id] = Book(new_id, title, author)
            print(Color.GREEN + f"✅ Success! '{title}' added with ID: {new_id}" + Color.RESET)
            
        elif choice == '2':
            b_id = input("Enter Book ID to delete (e.g., B1001): ").strip().upper()
            if b_id in self.books:
                # Input Validation & Confirmation Prompt
                confirm = input(Color.YELLOW + f"⚠️ Are you sure you want to delete '{self.books[b_id].title}'? (Y/N): " + Color.RESET).strip().upper()
                if confirm == 'Y':
                    del self.books[b_id]
                    print(Color.GREEN + f"✅ Book {b_id} deleted successfully." + Color.RESET)
                else:
                    print(Color.CYAN + "Deletion cancelled." + Color.RESET)
            else:
                print(Color.RED + "❌ Book ID not found!" + Color.RESET)

    # --- MENU 2: ISSUE BOOK ---
    def issue_book(self):
        print(Color.CYAN + "\n--- 📖 Issue Book ---" + Color.RESET)
        b_id = input("Enter Book ID: ").strip().upper()
        
        if b_id in self.books:
            book = self.books[b_id]
            if book.is_issued:
                print(Color.RED + f"❌ Sorry, '{book.title}' is already issued to {book.issued_to}." + Color.RESET)
            else:
                student = input("Enter Student Name/Roll: ").strip().title()
                if student:
                    book.is_issued = True
                    book.issued_to = student
                    print(Color.GREEN + f"✅ Success! '{book.title}' has been issued to {student}." + Color.RESET)
                else:
                    print(Color.RED + "❌ Student Name cannot be empty!" + Color.RESET)
        else:
            print(Color.RED + "❌ Book ID not found!" + Color.RESET)

    # --- MENU 3: RETURN BOOK ---
    def return_book(self):
        print(Color.CYAN + "\n--- ↩️ Return Book ---" + Color.RESET)
        b_id = input("Enter Book ID: ").strip().upper()
        
        if b_id in self.books:
            book = self.books[b_id]
            if book.is_issued:
                print(Color.GREEN + f"✅ Success! '{book.title}' (issued to {book.issued_to}) has been returned." + Color.RESET)
                book.is_issued = False
                book.issued_to = ""
            else:
                print(Color.YELLOW + f"⚠️ '{book.title}' is not currently issued to anyone." + Color.RESET)
        else:
            print(Color.RED + "❌ Book ID not found!" + Color.RESET)

    # --- MENU 4: SEARCH & REPORTS ---
    def search_and_reports(self):
        print(Color.CYAN + "\n--- 🔍 Search & Reports ---" + Color.RESET)
        print("1. View All Books")
        print("2. Search by Title or Author")
        print("3. View Issued Books")
        
        choice = input("Select an option: ")
        results = []
        
        if choice == '1':
            results = list(self.books.values())
        elif choice == '2':
            query = input("Enter search keyword: ").strip().lower()
            results = [b for b in self.books.values() if query in b.title.lower() or query in b.author.lower()]
        elif choice == '3':
            results = [b for b in self.books.values() if b.is_issued]
        else:
            print(Color.RED + "❌ Invalid choice." + Color.RESET)
            return

        self.display_table(results)

    def display_table(self, book_list):
        if not book_list:
            print(Color.YELLOW + "\n📭 No books found." + Color.RESET)
            return
            
        print(Color.MAGENTA + f"\n{'-'*80}")
        print(f"{'ID':<8} | {'Title':<25} | {'Author':<20} | {'Status':<20}")
        print(f"{'-'*80}" + Color.RESET)
        
        for book in book_list:
            status = f"Issued to {book.issued_to}" if book.is_issued else "Available"
            # Truncate long titles/authors for neat table formatting
            title = (book.title[:22] + '...') if len(book.title) > 25 else book.title
            author = (book.author[:17] + '...') if len(book.author) > 20 else book.author
            
            print(f"{book.book_id:<8} | {title:<25} | {author:<20} | {status:<20}")
        print(Color.MAGENTA + f"{'-'*80}" + Color.RESET)

    # --- UI BANNER ---
    def display_banner(self):
        now = datetime.datetime.now().strftime("%A, %d %b %Y | %I:%M %p")
        banner = f"""{Color.CYAN}{Color.BOLD}
=======================================================
   📚 L I B R A R Y   M A N A G E M E N T   S Y S T E M 
=======================================================
{Color.YELLOW}🕒 {now}
        """
        print(banner)

    # --- MAIN LOOP ---
    def run(self):
        self.load_data()
        
        while True:
            self.display_banner()
            print("1. 📚 Book Management")
            print("2. 📖 Issue Book")
            print("3. ↩️ Return Book")
            print("4. 🔍 Search & Reports")
            print("5. 💾 Save / Load Data")
            print("6. 🚪 Exit")
            
            try:
                choice = input(Color.BOLD + "\nEnter your choice (1-6): " + Color.RESET)
                
                if choice == '1': self.book_management()
                elif choice == '2': self.issue_book()
                elif choice == '3': self.return_book()
                elif choice == '4': self.search_and_reports()
                elif choice == '5': self.save_data()
                elif choice == '6':
                    self.save_data(auto_save=True)
                    print(Color.GREEN + "\n👋 Goodbye! System shutting down safely." + Color.RESET)
                    break
                else:
                    print(Color.RED + "❌ Invalid choice! Please enter a number between 1 and 6." + Color.RESET)
            except Exception as e:
                print(Color.RED + f"❌ An unexpected error occurred: {e}" + Color.RESET)

if __name__ == "__main__":
    app = LibraryManager()
    app.run()