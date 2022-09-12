Sun Dec 16 09:51:27 2012 > started the contest
Sun Dec 16 09:51:35 2012 > reading problem 1
Sun Dec 16 09:55:13 2012 > thinking solution 1
Sun Dec 16 09:56:04 2012 > stop thinking solution, reading problem 2
Sun Dec 16 09:58:10 2012 > finished reading problem 2, reading problem 3
Sun Dec 16 09:59:39 2012 > #3 is confusing
Sun Dec 16 10:01:45 2012 > #3 understood, returning to problem 1
Sun Dec 16 10:02:00 2012 > #1 is probably a floodfill
Sun Dec 16 10:02:50 2012 > considering floodfill by cows on #1
Sun Dec 16 10:07:11 2012 > we probably have to use computation geo for #1
Sun Dec 16 10:09:08 2012 > starting program for #1
Sun Dec 16 10:13:35 2012 > suspect that computational geo template is not correct, may have bugs
Sun Dec 16 10:13:44 2012 > finished input of #1
Sun Dec 16 10:14:44 2012 > debug pass
Sun Dec 16 10:17:32 2012 > checked book for other algorithms
Sun Dec 16 10:17:35 2012 > no success
Sun Dec 16 10:17:59 2012 > bfs floodfill on #1
Sun Dec 16 10:22:52 2012 > considering other algorithms for #1
Sun Dec 16 10:23:07 2012 > floodfill doesn't seem possible, memory constraints
Sun Dec 16 10:25:18 2012 > looking back at #1, sees that lines can only have 2 others connecting with it
Sun Dec 16 10:26:50 2012 > need algorithm to see if point is in shape...
Sun Dec 16 10:30:02 2012 > algorithm found! if two points are identical in terms of side of a line for the lines that form a whole shape, then they are in the same community
Sun Dec 16 10:33:28 2012 > if shape is inside another shape... we have a problem
Sun Dec 16 10:35:57 2012 > new algorithm: go through shapes and detect if points are inside the shapes. Then, the cows that are inside the same combination of shapes are the ones that are in the same community
Sun Dec 16 10:36:30 2012 > checking for exceptions
Sun Dec 16 10:36:49 2012 > calculating time to use for this algorithm
Sun Dec 16 10:38:08 2012 > time check pass. We are behind. Beginning program #1 again immediately
Sun Dec 16 10:50:34 2012 > successfully completed shapefinder
Sun Dec 16 11:00:44 2012 > back from a 2 min break
Sun Dec 16 11:00:57 2012 > giving up on #1 for now, going to return to it later
Sun Dec 16 11:01:03 2012 > rereading #2
Sun Dec 16 11:01:44 2012 > cooking up algorithm for #2
Sun Dec 16 11:04:14 2012 > can't brute force #2... searching for a better algorithm
Sun Dec 16 11:13:45 2012 > maybe critical point #2? calculating time
Sun Dec 16 11:14:33 2012 > Dynamic programming for #2
Sun Dec 16 11:15:26 2012 > Confirm: dynamic programming for #2. Time constraints work.
Sun Dec 16 11:15:34 2012 > Starting #2 program.
Sun Dec 16 11:35:07 2012 > Debugging #2
Sun Dec 16 11:41:39 2012 > Program #2 seems to work
Sun Dec 16 11:43:24 2012 > The largest test case we generated timeouts
Sun Dec 16 11:47:44 2012 > Some bugs remain in #2, but we have to move on to #3
Sun Dec 16 11:53:07 2012 > returning to problem 1
Sun Dec 16 12:05:58 2012 > #3 is probably a network flow algorithm
Sun Dec 16 12:30:59 2012 > can't find a solution to #1
Sun Dec 16 13:07:01 2012 > no progress
Sun Dec 16 13:09:57 2012 > giving up on contest
