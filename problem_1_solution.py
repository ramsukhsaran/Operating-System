import threading
import time
import random

# Semaphore initialization for each item (pen, paper, and question paper)
pen_sem = threading.Semaphore(0)
paper_sem = threading.Semaphore(0)
qpaper_sem = threading.Semaphore(0)

# Teacher's function
def teacher():
    items = ['pen', 'paper', 'qpaper']
    
    while True:
        # Randomly place two items on the table
        item1, item2 = random.sample(items, 2)  # Pick two random items
        print(f"Teacher places {item1} and {item2} on the table.")
        
        # Signal the two semaphores corresponding to the items placed
        if item1 == 'pen' and item2 == 'paper':
            pen_sem.release()
            paper_sem.release()
        elif item1 == 'pen' and item2 == 'qpaper':
            pen_sem.release()
            qpaper_sem.release()
        elif item1 == 'paper' and item2 == 'qpaper':
            paper_sem.release()
            qpaper_sem.release()
        
        # Wait for all students to finish their work (this can be handled in the student process)
        time.sleep(random.uniform(1, 3))  # Teacher takes some time before placing the next set of items

# Student function
def student(name, my_item, wait_for_1, wait_for_2, semaphore):
    while True:
        print(f"{name} waiting for {wait_for_1} and {wait_for_2} to be placed on the table.")
        
        # Wait until the other two items are placed on the table
        threading.Semaphore.wait(wait_for_1)
        threading.Semaphore.wait(wait_for_2)
        
        # Wait until the student can acquire their own item
        semaphore.acquire()
        
        # Perform the assignment
        print(f"{name} has all items and is doing the assignment.")
        time.sleep(random.uniform(1, 3))  # Simulate assignment time
        
        # Inform the teacher the work is done
        print(f"{name} has completed the assignment.")
        semaphore.release()

# Create student threads
student1 = threading.Thread(target=student, args=("Student 1 (Pen)", 'pen', paper_sem, qpaper_sem, pen_sem))
student2 = threading.Thread(target=student, args=("Student 2 (Paper)", 'paper', pen_sem, qpaper_sem, paper_sem))
student3 = threading.Thread(target=student, args=("Student 3 (Question Paper)", 'qpaper', pen_sem, paper_sem, qpaper_sem))

# Create teacher thread
teacher_thread = threading.Thread(target=teacher)

# Start the threads
teacher_thread.start()
student1.start()
student2.start()
student3.start()

# Wait for threads to finish (this is for demonstration purposes, this would actually be running indefinitely)
teacher_thread.join()
student1.join()
student2.join()
student3.join()
