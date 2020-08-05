# 定义Task类， 将coroutine 绑定在Task上，调度器调度Task
# 当Task 被调度时，其绑定的coroutine 被执行
class Task(object):
    #静态成员
    taskid = 0
    # 初始化Task, target 是被执行的单元，必须是一个coroutine
    def __init__(self, target):
        #使用静态成员
        Task.taskid +=1 
        self.tid = Task.taskid
        self.target = target
        self.sendval = None
    # 当task被调度时，task 的run()函数被调度器调度。
    # task 通过向其taget 发送send()来触发其执行
    # 所以target 必须是一个coroutine
    def run(self):
        return self.target.send(self.sendval)

#调度器    
class Scheduler(object):
    def __init__(self):
        # runnable task 被放入ready队列
        # shedule会从ready中取出task,将其运行 
        self.ready = Queue()
        # 所有被sheduler管理的task
        self.taskmap = {}

    def new(self,target):
        # 创建task
        newtask = Task(target)
        # 将task放入map
        self.taskmap[newtask.tid] = newtask
        # 新的task是被调度的，放入队列，等待执行
        self.shedule(newtask)
        return newtask.tid

    
        
