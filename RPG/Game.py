import pygame
import sys
import time

from Source.tutorial import map_list, GAME_OVER, START
from Objects import *
from config import *

class Game:
  def __init__(self):
    pygame.init()
    self.screen = pygame.display.set_mode((WIN_WIDTH, WIN_HEIGTH))
    self.clock = pygame.time.Clock()
    self.font = pygame.font.Font('Fonts/misaki_gothic.ttf', 32)
    self.running = True
    self.playing = True

    self.all_sprites = pygame.sprite.LayeredUpdates()
    self.player = pygame.sprite.LayeredUpdates()
    self.Player = 0
    self.rocks = pygame.sprite.LayeredUpdates()
    self.warp = pygame.sprite.LayeredUpdates()
    self.win = pygame.sprite.LayeredUpdates()
    self.win_list = []
    self.warp_list = []
    self.collide_list = []
    self.buttons_gui = pygame.sprite.LayeredUpdates()
    self.enemies = pygame.sprite.LayeredUpdates()
    self.attacks = pygame.sprite.LayeredUpdates()
    self.current_map = 0

  def events(self):
    for events in pygame.event.get():
      if events.type == pygame.QUIT:
        self.playing = False
        self.running = False

  def update(self):
    self.all_sprites.update()

  def draw(self):
    self.screen.fill(BLACK)
    self.all_sprites.draw(self.screen)
    self.clock.tick(FPS)
    pygame.display.update()

  def clear_screen(self):
    self.all_sprites.empty()
    del self.collide_list[:]
    del self.warp_list[:]
    del self.win_list[:]

  def main(self):
    self.Titlemap(map_list[self.current_map])
    while self.playing:
      self.events()
      self.update()
      self.draw()
    self.clear_screen()

  def Titlemap(self, map):
    for y, row in enumerate(map):
      for x, column in enumerate(row):
        if column == "R":
          self.collide_list.append(Rock(self, x, y))
        if column == "P":
          self.Player = Player(self, x, y)
        if column == "r" or column == "g" or column == "b":
          Button_GUI(self, x, y, column)
        if column == "W":
          self.warp_list.append(Warp(self, x, y))
        if column == "I":
          self.win_list.append(Win(self, x, y))

  def game_over(self):
    while self.running:
      self.Titlemap(GAME_OVER)
      self.events()
      self.update()
      self.draw()
      if (self.playing == True):
        self.clear_screen()
        self.main()

  def intro_screen(self):
    self.playing = False
    self.Titlemap(START)
    while self.running:
      self.events()
      self.update()
      self.draw()
      if (self.playing == True):
        self.clear_screen()
        break

g = Game()
g.intro_screen()
while g.running:
  g.main()
  g.game_over()
pygame.quit()
sys.exit()