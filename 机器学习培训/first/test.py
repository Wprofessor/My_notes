def myAtoi( str):
    """
    :type str: str
    :rtype: int
    """
    if len(str) == 0:
        return 0
    if str[0:1].isalpha():
        return 0
    else:
        word = ""
        if str[0] == '-':
            for i in range(1, len(str)):
                if str[i].isdigit():
                    word += str[i]
                else:
                    break
            if int(word) > 2 ** 31:
                return -2147483648
            else:
                return -1 * int(word)

        else:
            for i in range(len(str)):
                if str[i].isdigit():
                    word += str[i]
                else:
                    break
            if int(word) > 2 ** 31:
                return 2147483648
            else:
                return int(word)


print(myAtoi("91332htr"))
print("     -42" .strip())