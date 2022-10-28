Mon Feb 23 19:57:48 2015 > 2015 February (Gold)
Mon Feb 23 19:58:09 2015 > I'll cut to the chase here. If you want some background, consult the Journal.
Mon Feb 23 19:59:59 2015 > Let's go!
Mon Feb 23 20:01:01 2015 > 1 seems to be DP with optimization
Mon Feb 23 20:02:25 2015 > 2 could probably be done with Rabin-Karp hashing
Mon Feb 23 20:09:39 2015 > 3 could be sped up with convex hull (dynamic) but I'm not sure of details
Mon Feb 23 20:09:52 2015 > I'll think about that one a bit more before returning to 1 and 2
Mon Feb 23 20:15:07 2015 > We can maintain incremental convex hull of herd, now we need to find if a line intersects a the convex polygon.
Mon Feb 23 20:18:31 2015 > The line problem can be accomplished with a binary search on slope, since slope is increasing/decreasing monotonically in top/bot parts of hull.
Mon Feb 23 20:26:42 2015 > There are a few edge cases, but it shouldn't take more than an hour if it all goes well.
Mon Feb 23 20:26:51 2015 > Back to 1
Mon Feb 23 20:27:34 2015 > 3 is NlogN
Mon Feb 23 20:32:37 2015 > 1 we can use Fenwick tree and will be done
Mon Feb 23 20:35:24 2015 > Hmm, 2 isn't what I made it out to be.
Mon Feb 23 20:44:16 2015 > I'm not too sure about 2... shoot, time is running out.
Mon Feb 23 20:47:47 2015 > Actually, tries.
Mon Feb 23 20:49:13 2015 > Yes, tries will work for 2!
Mon Feb 23 20:50:37 2015 > Alright, we need to hurry, starting with 1, then 2, then 3
Mon Feb 23 20:58:03 2015 > Actually, 1 doesn't need fenwick.
Mon Feb 23 21:01:41 2015 > Checking 1...
Mon Feb 23 21:01:48 2015 > Dang, it's all wrong...
Mon Feb 23 21:02:28 2015 > Debugging...
Mon Feb 23 21:18:25 2015 > Alright, I have a memory conservation technique for 1
Mon Feb 23 21:43:19 2015 > Stuck on 1, this is bad...
Mon Feb 23 21:50:19 2015 > I need to move on... to 2
Mon Feb 23 22:07:17 2015 > Trying 2
Mon Feb 23 22:07:22 2015 > All wrong...
