import os
import ppft 


def find_all(name, path):
    result = []
    for root, dirs, files in os.walk(path):
        if name in files:
            result.append(os.path.join(root, name))
    return result


def find(dir):
    reverse = str(dir[::-1])
    find = reverse.find('/')
    delete = reverse[find:]
    final = delete[::-1]
    return final[:-1]

def check(path):
    rev = str(path[::-1])
    s = rev.find('/')
    res = rev[:s]
    return res[::-1]

if '__main__' == __name__ :
    file = ppft.__file__
    dir = os.path.dirname(file)
 
    for i in range(len(file)):
        if i == 0:
            find_file = find(dir)
        else:
            find_file = find(find_file)
        res = str(find_all('ppserver', find_file))
        r = res[:-2]
        if check(r) == 'ppserver':
            os.environ['PATH'] = str(res)
            print(os.environ['PATH'])
            break
        else:
            find(find_file)
