class CCApp:
    def __init__(self, inter):
        self.xRate = {'USD':6.306,
                      'Euro':8.2735,
                      'Yen':0.0775,
                      'Pound':10.0486}
        self.interface = inter

    def run(self):
        while True:
            qFlag,fc,to,amount = self.interface.getInfo()
            if qFlag:
                break
            elif to == 'RMB':
                result = amount * self.xRate[fc]
            else:
                result = amount / self.xRate[fc]
            self.interface.showInfo(result)

