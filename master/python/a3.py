
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
        self._master.title("Simple Tile Game")

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

class SimpleStatusBar(SimpleTileApp):
    def __init__(self, player):
        """
        Constructor(SimpleStatusBar, tk.Frame)
        """
        self._master = player
        #self._frame = tk.Frame(self._master)
        #self._frame.pack(side=tk.TOP)
        
        self.score = self._master.get_score()
        self.l_score = tk.Label(self._master._master, text="Score: %d" %self.score)
        self.l_score.pack(side=tk.LEFT)
        
        self.count = self._master.get_swaps()
        self.l_count = tk.Label(self._master._master, text="Swap NO.: %d" %self.count)
        self.l_count.pack(side=tk.LEFT)

        self.button = tk.Button(self._master._master, text = "Reset", command = self.reset_bar)
        self.button.pack(side=tk.RIGHT)

        self.menubar = tk.Menu(self._master._master)
        self.filemenu = tk.Menu(self.menubar, tearoff=0)
        self.filemenu.add_command(label="New Game", command=self.new_game)
        
        self.filemenu.add_separator()
        self.filemenu.add_command(label="Exit", command=self._master._master.quit)
        self.menubar.add_cascade(label="File", menu=self.filemenu)

        self.helpmenu = tk.Menu(self.menubar, tearoff=0)
        self.helpmenu.add_command(label="About", command=self.help_game)
        self.menubar.add_cascade(label="Help", menu=self.helpmenu)
        
        player._game.on('swap', self.display_swap)
        player._game.on('score', self.display_score)
    
    def display_score(self, score):
        self.score = self._master.get_score()
        self.l_score.config(text="Score: %d" %self.score)

    def display_swap(self, from_pos, to_pos):
        self.count = self._master.get_swaps()
        self.l_count.config(text="Swap NO.: %d" %self.count)

    def reset_bar(self):
        self._master.reset_score()
        self._master.reset_swaps()
        self.score = self._master.get_score()
        self.l_score.config(text="Score: %d" %self.score)
        self.count = self._master.get_swaps()
        self.l_count.config(text="Swap NO.: %d" %self.count)

    def new_game(self):
        #self._master._game.reset()
        self.reset_bar()

    def help_game(self):
        pass


def task1():
    # Add task 1 GUI instantiation code here
    print ("Hello World")
    top = tk.Tk()
    player = SimpleTileApp(top)
    #score = player.get_score()
    #count = player.get_swaps()
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
    top.config(menu=bar.menubar)
    top.mainloop()
    pass

class Character(SimpleTileApp):
    def __init__(self,max_health):
        self._max_health = max_health
        
    def get_max_health(self):
        return self._max_health
    
    def get_health(self):
        return self._max_health

    def lose_health(self,amount):
        self._current_health = self._max_health - amount

    def gain_health(self, amount):
        self._max_health = self._current_health + amount

    def reset_health(self):
        self._current_health = max_health

class Enemy(Character):
        def __init__(self, type, max_health, attack):
            super().__init__(max_health)
            self._type = type
            self._attack = attack
            a,b = self._attack
        
        def get_type(self):
            return self._type

        def attack(self):
            a,b = self._attack
            return random.randint(a,b)
            #return random.randrange(a,b)

class Player(Character):
        def __init__(self, max_health, swaps_per_turn, base_attack):
            super().__init__(max_health)
            self._swap_per_turn = swaps_per_turn
            self._base_attack = base_attack

        def record_swap(self):
            self._swap_per_turn = self._swap_per_turn -1
            if self._swap_per_turn > -1:
                return self._swap_per_turn
            else:
                return 0

        def get_swaps(self):
            return self._swap_per_turn

        def reset_swaps(self): 
            pass
        
        def attack(self, runs, defender_type):
            self._base_attack = base_attack
            #runs = [Run(defender_type),]
            return [(self._defender_type1),(self._defender_type2)]
        
class VersusStatusBar(tk.Frame):
        def __init__(self,master):

            super().__init__(master)
            self._new_player_health = 0
            self._new_enemy_health = 0 
            self._new_num_of_swaps = 0
            self._label1 = tk.Label(master, text = "current Level:1", bg = 'white')
            self._label1.pack()
            self._label2 = tk.Label(master, text = "Player Health:0", bg = 'white')
            self._label2.pack(side = tK.LEFT)
            self._label3 = tk.Label(master, text = "Enemy Health:0", bg = 'white')
            self._label3.pack(side = tK.LEFT)
            self._label4 = tk.Label(master, text = "Number of swaps:0", bg = 'white')
            self._label4.pack(side = tK.LEFT)
        
        def update_health_player(self,score):
            self._new_player_health += score
            pass

        def update_health_enemy(self):
            pass
        
class SinglePlayerTileApp(SimpleTileApp):
        def __init__(self,master):
            self._master = master
            self._text = tk.Text(master)
            self._game = SimpleGame
            self._game.on('swap',self._handle_swap)
            self._game.on('score',self._handle_score)

            self._grid_view = TileGridView(
                    master.self._game.get_grid(),
                    width = GRID_WIDTH, height = GRID_HEIGHT,bg = 'black')
            self._grid_view.pack(side=tk.TOP,expand = True, fill = tk.BOTH)

            self._master.title(Level1)
            menubar = tk.Menu(master)
            master.config (menu = menubar)
            self.filemenu = tk.Menu(self.menubar, tearoff=0)
            self.menubar.add_cascade(label="File", menu=self.filemenu)
            self.filemenu.add_command(label="New Game", command=self.new_game)
            self.filemenu.add_command(label="Exit", command=self.exit)
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
