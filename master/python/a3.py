#!/usr/bin/env python3
################################################################################
#
#   CSSE1001/7030 - Assignment 3
#
#   Student Username: s4401031
#
#   Student Name: Xiaoyu Shang
#
################################################################################

# VERSION 1.0.2

################################################################################
#
# The following is support code. DO NOT CHANGE.

from a3_support import *


# End of support code
################################################################################
# Write your code below
################################################################################

# Write your classes here (including import statements, etc.)


class SimpleTileApp(object):
    def __init__(self, master):
        """
        Constructor(SimpleTileApp, tk.Frame)
        """
        self._master = master
        self._master.title("Puzzle Game")

        self._game = SimpleGame()

        self._game.on('swap', self._handle_swap)
        self._game.on('score', self._handle_score)

        self._grid_view = TileGridView(
            master, self._game.get_grid(),
            width=GRID_WIDTH, height=GRID_HEIGHT, bg='black')
        self._grid_view.pack(side=tk.TOP, expand=True, fill=tk.BOTH)
        
        # Add your code here

        self.score = 0
        self.swap_count = 0


    def _handle_swap(self, from_pos, to_pos):
        """
        Run when a swap on the grid happens.
        """
        self.record_swap()
        print("SimplePlayer made a swap from {} to {}!".format(
            from_pos, to_pos))

    def _handle_score(self, score):
        """
        Run when a score update happens.
        """
        self.add_score(score)
        print("SimplePlayer scored {}!".format(score))

    def add_score(self, score):
        self.score = self.score + score
        print("score is", self.score)

    def get_score(self):
        return self.score

    def reset_score(self):
        self.score = 0

    def record_swap(self):
        self.swap_count = self.swap_count + 1

    def get_swaps(self):
        return self.swap_count

    def reset_swaps(self):
        self.swap_count = 0

class SimpleStatusBar(object):
    def __init__(self, master, score, swap_count):
        """
        Constructor(SimpleStatusBar, tk.Frame)
        """
        self._master = master
        self._frame = tk.Frame(self._master)
        self._frame.pack()
        
        #self.score = master.get_score()
        #l_score = tk.Label(self._frame, textvariable=self.score, relief=tk.RAISED)
        #l_socre.pack(side=tk.LEFT)


def task1():
    # Add task 1 GUI instantiation code here
    print ("Hello World")
    top = tk.Tk()
    player = SimpleTileApp(top)
    bar = SimpleStatusBar(player)
    """
    player.add_score(9001)
    player.reset_score()
    score = player.get_score()
    print("score is", score)
    player.record_swap()
    count = player.get_swaps()
    print("count is", count)
    player.reset_swaps()
    count = player.get_swaps()
    print("count is", count)
    """
    top.mainloop()
    pass


def task2():
    # Add task 2 GUI instantiation code here
    pass


def task3():
    # Add task 3 GUI instantiation code here
    pass


def main():
    # Choose relevant task to run
    task1()


if __name__ == '__main__':
    main()
