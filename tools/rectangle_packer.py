# coding: utf-8

class Rectangle:

    def __init__(self):
        self.name = ''
        self.x = 0
        self.y = 0
        self.width = 0
        self.height = 0
        self.rotate = False

    def isOverlapped(self, rhs):
        return (self.x < rhs.x + rhs.width) \
    and (rhs.x < self.x + self.width) \
    and (self.y < rhs.y + rhs.height) \
    and (rhs.y < self.y + self.height)

class RectanglePacker:

    def __init__(self):
        self.maxSize = 1024
        self.margin = 0
        self.inputs = list()
        self.outputs = list()

    def append(self, name, size):
        if size[0]+2*self.margin>self.maxSize or size[1]+2*self.margin>self.maxSize:
            print('{0} is over size'.format(name) )
            return
        self.inputs.append( {'name':name, 'size':size} )

    def powerOf2(self, size):
        width = 1
        height = 1

        while width < size[0]:
            width *= 2
        while height < size[1]:
            height *= 2

        return (width, height)

    def isOverlapped(self, rect, rectList):
        for deployedRect in rectList:
            if rect.isOverlapped(deployedRect):
                return True
        return False

    def addToOutput(self, rect):

        candidate = set()

        for output in self.outputs:
            rectList = output['rectangles']
            width = output['size'][0]
            height = output['size'][1]
            for deployedRect in rectList:
                for deployedRect2 in rectList[rectList.index(deployedRect):]:

                    def checkAndAdd(r):
                        if self.isOverlapped( r, rectList ):
                            return
                        if ( r.x + r.width > width ):
                            return
                        if( r.y + r.height > height ):
                            return
                        candidate.add( (r.x, r.y) )

                    #
                    rect.x = deployedRect.x + deployedRect.width + self.margin
                    rect.y = deployedRect2.y

                    checkAndAdd(rect)

                    #
                    rect.x = deployedRect.x
                    rect.y = deployedRect2.y + deployedRect2.height + self.margin
                    checkAndAdd(rect)

                    #
                    rect.x = deployedRect.x + deployedRect.width + self.margin
                    rect.y = deployedRect2.y + deployedRect2.height + self.margin
                    checkAndAdd(rect)

                    if (deployedRect.x==deployedRect2.x ) and (deployedRect.y==deployedRect2.y ):
                        continue

                    #
                    rect.x = deployedRect2.x + deployedRect2.width + self.margin
                    rect.y = deployedRect.y

                    checkAndAdd(rect)

                    #
                    rect.x = deployedRect2.x
                    rect.y = deployedRect.y + deployedRect.height + self.margin
                    checkAndAdd(rect)

                    #
                    rect.x = deployedRect2.x + deployedRect2.width + self.margin
                    rect.y = deployedRect.y + deployedRect.height + self.margin
                    checkAndAdd(rect)


            if len(candidate)>0:
                candidate = list(candidate)
                candidate.sort(key=lambda x: x[0]*x[0]+x[1]*x[1])
                pos = candidate[0]
                rect.x = pos[0]
                rect.y = pos[1]
                output['rectangles'].append(rect)
                return True


        return False

    def expandOutputSize(self):
        for output in self.outputs:
            if output['size'][0] <= output['size'][1]:
                if 2*output['size'][0] <= self.maxSize:
                    output['size'] = (2*output['size'][0], output['size'][1])
                    return True
            else:
                if 2*output['size'][1] <= self.maxSize:
                    output['size'] = (output['size'][0], 2*output['size'][1])
                    return True

        return False


    def calculate(self):
        for nameSize in sorted(self.inputs, key=lambda x: max(x['size'][0], x['size'][1]), reverse=True):

            rect = Rectangle()
            rect.name = nameSize['name']
            rect.width = nameSize['size'][0]
            rect.height = nameSize['size'][1]

            add = False
            while not add:
                if self.addToOutput(rect):
                    add = True
                    break

                # swap width, height
                rect.width, rect.height = rect.height, rect.width
                rect.rotate = True

                if self.addToOutput(rect):
                    add = True
                    break

                # swap width, height
                rect.width, rect.height = rect.height, rect.width
                rect.rotate = False

                if not self.expandOutputSize():
                    break

            if add:
                continue

            rect.x = self.margin
            rect.y = self.margin

            self.outputs.append( { 'size':self.powerOf2((rect.width+self.margin, rect.height+self.margin)), 'rectangles':[rect] } )


def test():
    packer = RectanglePacker()
    packer.margin = 1
    packer.append('rect_1', (54, 25) )
    packer.append('rect_2', (23, 47) )
    packer.append('rect_3', (34, 112))
    packer.append('rect_4', (14, 55) )
    packer.append('rect_5', (63, 74) )
    packer.append('rect_6', (34, 111))

    packer.calculate()
    for output in packer.outputs:
        print(output['size'])
        for rect in output['rectangles']:
            print( '{0}: ({1},{2}), ({3},{4}), rotate:{5}'.format(rect.name, rect.x, rect.y, rect.width, rect.height, rect.rotate) )


if __name__=='__main__':
    test()
