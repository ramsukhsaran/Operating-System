from collections import deque

class Person:
    def __init__(self, name, role, arrival_time, service_time):
        self.name = name
        self.role = role  # "teacher" or "student"
        self.arrival_time = arrival_time
        self.service_time = service_time


def library_simulation(people, max_teacher_streak=3):
    time = 0
    teacher_queue = deque()
    student_queue = deque()

    teacher_streak = 0
    completed = []

    people = sorted(people, key=lambda x: x.arrival_time)
    i = 0

    while i < len(people) or teacher_queue or student_queue:

        # Add arrivals to queues
        while i < len(people) and people[i].arrival_time <= time:
            if people[i].role == "teacher":
                teacher_queue.append(people[i])
            else:
                student_queue.append(people[i])
            i += 1

        # Decide who gets service
        if teacher_queue and (teacher_streak < max_teacher_streak or not student_queue):
            current = teacher_queue.popleft()
            teacher_streak += 1
        elif student_queue:
            current = student_queue.popleft()
            teacher_streak = 0
        else:
            time += 1
            continue

        # Service current person
        start_time = time
        time += current.service_time
        completed.append((current.name, current.role, start_time, time))

    return completed


# ---------------- Example Usage ----------------

people = [
    Person("T1", "teacher", 0, 3),
    Person("S1", "student", 1, 2),
    Person("T2", "teacher", 2, 3),
    Person("T3", "teacher", 3, 2),
    Person("S2", "student", 4, 1),
    Person("T4", "teacher", 5, 2),
]

result = library_simulation(people)

for r in result:
    print(f"{r[0]} ({r[1]}) served from time {r[2]} to {r[3]}")
