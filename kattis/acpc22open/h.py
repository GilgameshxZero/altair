def main():
    n: int = int(input())

    # Read in the next line
    line: str = input()

    # Example line: "1 + 2 + 3"
    # Split into a list of numbers and ops
    # ["1", "+", "2", "+", "3"]
    xs = line.split()

    # Convert the numbers to ints
    # [1, "+", 2, "+", 3]
    xs = [int(x) if x.isdigit() else x for x in xs]

    memo = {}
    def get_min_max(beg: int, end: int):
        if (beg, end) in memo:
            return memo[(beg, end)]

        if end - beg == 1:
            return xs[beg], xs[beg]

        if end - beg == 2:
            if xs[beg] == "+":
                return xs[beg + 1], xs[beg + 1]
            elif xs[beg] == "-":
                return -xs[beg + 1], -xs[beg + 1]
            else:
                assert False

        mn, mx = None, None

        # Split at plus node
        for i, x in enumerate(xs[beg:end]):
            if x == "+" and i != 0:
                # Recursively get min/max of left and right
                left_min, left_max = get_min_max(beg, beg + i)
                right_min, right_max = get_min_max(beg + i + 1, end)

                cmn = left_min + right_min
                cmx = left_max + right_max

                mn = cmn if mn is None else min(mn, cmn)
                mx = cmx if mx is None else max(mx, cmx)

        # Split at minus node
        for i, x in enumerate(xs[beg:end]):
            if x == "-" and i == 0:
                right_min, right_max = get_min_max(beg + 1, end)

                cmn = -right_max
                cmx = -right_min

                mn = cmn if mn is None else min(mn, cmn)
                mx = cmx if mx is None else max(mx, cmx)

            if x == "-" and i != 0:
                # Recursively get min/max of left and right
                left_min, left_max = get_min_max(beg, beg + i)
                right_min, right_max = get_min_max(beg + i + 1, end)

                cmn = left_min - right_max
                cmx = left_max - right_min

                mn = cmn if mn is None else min(mn, cmn)
                mx = cmx if mx is None else max(mx, cmx)

        # Split at product node
        for i, x in enumerate(xs[beg:end]):
            if isinstance(x, int) and beg + i + 1 < end:
                # Recursively get min/max of left and right
                left_min, left_max = get_min_max(beg, beg + i + 1)
                right_min, right_max = get_min_max(beg + i + 1, end)

                cmn = min(left_min * right_min, left_min * right_max, left_max * right_min, left_max * right_max)
                cmx = max(left_min * right_min, left_min * right_max, left_max * right_min, left_max * right_max)

                mn = cmn if mn is None else min(mn, cmn)
                mx = cmx if mx is None else max(mx, cmx)

        memo[(beg, end)] = (mn, mx)
        return mn, mx

    _, mx = get_min_max(0, len(xs))
    print(mx)

if __name__ == "__main__":
    main()
