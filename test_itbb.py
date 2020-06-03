import os

# file_list = ["100.txt", "500.txt", "1000.txt", "10000.txt", "50000.txt", "100000.txt"]
file_list = ["100.txt", "500.txt", "1000.txt", "5000.txt", "10000.txt", "50000.txt", "100000.txt", "500000.txt", "1000000.txt"]

total_runs = 1000

results_file = "resultsITBB.txt"

def main():
    for file_name in file_list:
        for thread_count in range(1,9):
            total_time = 0
            run_count = 0
            for attempt in range(0,total_runs):
                try:
                    command = f"./oneTBB-tbb_2020/examples/quicksort_tbb/quicksort/quicksort {file_name} {thread_count}"
                    # print(f"executing: {command}")
                    output = os.popen(command).read()
                    # print(output)
                    # line_broken_output = output.split("\n")[2]
                    time_took = float(output.split(" ")[2])
                    total_time = total_time + time_took
                    run_count = run_count + 1
                    # print(time_took)
                except:
                    pass
            with open(results_file, "a+") as fp:
                fp.write("{}, {}, {:.3f}\n".format(file_name, thread_count, 1000 * total_time/run_count))
            print("Ran {} with {} thread(s). It took {:.3f} milliseconds on average".format(file_name, thread_count, 1000 * total_time/run_count))
            # print(f"Ran {file_name} with {thread_count} thread(s). It took {total_time/total_runs} seconds on average")

if __name__ == "__main__":
    main()