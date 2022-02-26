import pygame
from config import *
from Source.tutorial import map_list
import math
import random

class Player(pygame.sprite.Sprite):
  def __init__(self, game, x, y):
    self.game = game
    self._layer = PLAYER_LAYER
    self.group = self.game.all_sprites, self.game.player
    pygame.sprite.Sprite.__init__(self, self.group)
    self.x = x * TILE_SIZE
    self.y = y * TILE_SIZE
    self.change_x = 0
    self.change_y = 0
    self.height = TILE_SIZE
    self.width = TILE_SIZE
    self.Speed = PLAYER_SPEED

    self.image = pygame.Surface([self.width, self.height])
    self.image.fill(RED)
    self.rect = self.image.get_rect()
    self.rect.x = self.x
    self.rect.y = self.y

    self.hitbox = pygame.draw.rect(self.image, RED, (0,0, TILE_SIZE, TILE_SIZE))
    self.hitbox.x = self.x
    self.hitbox.y = self.y

  def update(self):
    self.movement()
    self.rect.x += self.change_x
    self.rect.y += self.change_y
    self.hitbox.x += self.change_x
    self.hitbox.y += self.change_y
    self.change_x = 0
    self.change_y = 0

  def movement(self):
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
      self.change_y -= PLAYER_SPEED
    if keys[pygame.K_s]:
      self.change_y += PLAYER_SPEED
    if keys[pygame.K_a]:
      self.change_x -= PLAYER_SPEED
    if keys[pygame.K_d]:
      self.change_x += PLAYER_SPEED

class Rock(pygame.sprite.Sprite):
  def __init__(self, game, x, y):
    self.game = game
    self._layer = BLOCK_LAYER
    self.group = self.game.all_sprites, self.game.rocks
    pygame.sprite.Sprite.__init__(self, self.group)
    self.x = x * TILE_SIZE
    self.y = y * TILE_SIZE
    self.height = TILE_SIZE
    self.width = TILE_SIZE
    self.image = pygame.Surface([self.width, self.height])
    self.image.fill(BLUE)
    self.rect = self.image.get_rect()
    self.rect.x = self.x
    self.rect.y = self.y
    self.hitbox = pygame.draw.rect(self.image, BLUE, (0,0, TILE_SIZE, TILE_SIZE))
    self.hitbox.x = self.x
    self.hitbox.y = self.y

  def update(self):
    if self.game.Player.hitbox.collidelist(self.game.collide_list) != -1:
      self.game.playing = False
      #print("I touch a rock!")

class Warp(pygame.sprite.Sprite):
  def __init__(self, game, x, y):
    self.game = game
    self._layer = WARP_LAYER
    self.group = self.game.all_sprites, self.game.warp
    pygame.sprite.Sprite.__init__(self, self.group)
    self.x = x * TILE_SIZE
    self.y = y * TILE_SIZE
    self.height = TILE_SIZE
    self.width = TILE_SIZE
    self.image = pygame.Surface([self.width, self.height])
    self.image.fill(WHITE)
    self.rect = self.image.get_rect()
    self.rect.x = self.x
    self.rect.y = self.y
    self.hitbox = pygame.draw.rect(self.image, WHITE, (0,0, TILE_SIZE, TILE_SIZE))
    self.hitbox.x = self.x
    self.hitbox.y = self.y

  def update(self):
    if self.game.Player.hitbox.collidelist(self.game.warp_list) != -1:
      self.game.clear_screen()
      self.game.current_map += 1
      self.game.Titlemap(map_list[self.game.current_map])
      print("I touched a warp!")

class Win(pygame.sprite.Sprite):
  def __init__(self, game, x, y):
    self.game = game
    self._layer = WIN_LAYER
    self.group = self.game.all_sprites, self.game.win
    pygame.sprite.Sprite.__init__(self, self.group)
    self.x = x * TILE_SIZE
    self.y = y * TILE_SIZE
    self.height = TILE_SIZE
    self.width = TILE_SIZE
    self.image = pygame.Surface([self.width, self.height])
    self.image.fill(GREEN)
    self.rect = self.image.get_rect()
    self.rect.x = self.x
    self.rect.y = self.y
    self.hitbox = pygame.draw.rect(self.image, GREEN, (0,0, TILE_SIZE, TILE_SIZE))
    self.hitbox.x = self.x
    self.hitbox.y = self.y

  def update(self):
    if self.game.Player.hitbox.collidelist(self.game.win_list) != -1:
      self.game.playing = False
      print("I finised the Game!")


class Button_GUI(pygame.sprite.Sprite):
  def __init__(self, game, x, y, sign):
    self.game = game
    self._layer = BUTTON_LAYER
    self.group = self.game.all_sprites, self.game.buttons_gui
    pygame.sprite.Sprite.__init__(self, self.group)
    self.x = x * TILE_SIZE
    self.y = y * TILE_SIZE
    self.height = TILE_SIZE * 2
    self.width = TILE_SIZE * 4

    self.color = self.Color_IT(sign)
    self.image = pygame.Surface([self.width, self.height])
    self.image.fill(self.color)
    self.rect = self.image.get_rect()
    self.rect.x = self.x
    self.rect.y = self.y

    self.hitbox = pygame.draw.rect(self.image, self.color, (0,0, self.width, self.height))
    self.hitbox.x = self.x
    self.hitbox.y = self.y

  def Color_IT(self, color):
    Color = {
      'r' : RED,
      'b' : BLUE,
      'a' : BLACK,
      'g' : GREEN,
      'w' : WHITE
    }
    return Color.get(color, WHITE)

  def update(self):
    pos = pygame.mouse.get_pos()
    if pygame.mouse.get_pressed()[0] and (self.hitbox.collidepoint(pos) and self.color == RED):
      self.game.running = False
      print("Exiting the Game!")
    elif pygame.mouse.get_pressed()[0] and (self.hitbox.collidepoint(pos) and self.color == GREEN):
      self.game.playing = True
      self.game.current_map = 0
      #print("Reading the Game!")
    elif pygame.mouse.get_pressed()[0] and (self.hitbox.collidepoint(pos) and self.color == BLUE):
      self.game.clear_screen()
      print("Main Menu!")
      self.game.intro_screen()
    else:
      pass


