class FunctionDeco(object):
    def __init__(self):
        self.freq = {}

    def __call__(self, function):
        if self.freq.has_key(function):
            self.freq[function] += 1
        else:
            self.freq[function] = 1
        
        freq = self.freq[function]
        if freq == 1:
            return function
        else:
            return function + "#" + str(freq)
