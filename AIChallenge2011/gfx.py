#! /usr/bin/env python

"""
    Graphics implementation of Tron output
    AI-Challenge 2011
    
    Innovision 2011
    Netaji Subhas Intitute of Technology
"""

import os
import pygame
from pygame.locals import *
from sys import exit
import random
from time import sleep

os.environ['SDL_VIDEO_CENTERED'] = '1'
pygame.init()

clock = pygame.time.Clock()
screen = pygame.display.set_mode((500, 500), 0, 32)

#Team Names
Team1 = "Player051"
Team2 = "Player052"

#Array for frame
arr = [0]*22

#Required drawing functions
def draw_block(x, y, color):
    pygame.draw.rect(screen, color,(20*x+51, 20*y+51, 19, 19))

def draw_head(x, y, color):
    pygame.draw.circle(screen, color, (20*x+61, 20*y+61), 9)

#For Text
HeadFont = pygame.font.Font(None, 50)

text = HeadFont.render(Team1 + ' VS ' + Team2, True, (25,255, 255), (159, 182, 205))
HeadRect = text.get_rect()
HeadRect.centerx = 250
HeadRect.centery = 25
screen.blit(text, HeadRect)

FootFont = pygame.font.Font(None, 24)

FootRect1 = text.get_rect()
FootRect1.centerx = 240
FootRect1.centery = 466

FootRect2 = text.get_rect()
FootRect2.centerx = 240
FootRect2.centery = 490

#Read the output file to get the frames and then reproduce it in pygame
f = open("tron.doc","r")
done = 0

while(1):
    screen = pygame.display.set_mode((500, 500), 0, 32)
    pygame.display.set_caption('Twisted Tron - AI Challenge 2011')
    for y in range(22):
        line = f.readline().replace('\n','')
        if len(line) == 0:
            done = 1
            break
        arr[y] = line

    if done == 1:
        break
    
    text1 = FootFont.render(str(arr[0]), True, (255,255, 255), (159, 182, 205))
    text2 = FootFont.render(str(arr[1]), True, (255,255, 255), (159, 182, 205))

    screen.blit(text1, FootRect1)
    screen.blit(text2, FootRect2)

    for x in range(20):
        for y in range(20):
            if arr[x+2][y] == 'A':
                color = (0, 255, 255)
                draw_head(y, x, color)
            
            if arr[x+2][y] == 'B':
                color = (255, 165, 0)
                draw_head(y, x, color)
            
            if arr[x+2][y] == 'F':
                color = (105, 105, 105)
                draw_block(y, x, color)
            
            if arr[x+2][y] == '.':
                color = (0, 0, 0)
                draw_block(y, x, color)
            
            if arr[x+2][y] == 'P':
                color = (106, 90, 205)
                draw_head(y, x, color)
            
            if arr[x+2][y] == 'a':
                color = (0, 255, 255)
                draw_block(y, x, color)
            
            if arr[x+2][y] == 'b':
                color = (255, 165, 0)
                draw_block(y, x, color)

    for events in pygame.event.get():
        if events.type == KEYDOWN:
            if events.key == 27:  # For escape key
                text = font.render("Game exited", 120, (124, 252, 0))
                textpos = text.get_rect()
                textpos.centerx = screen.get_rect().centerx
                textpos.centery = screen.get_rect().centery
                screen.blit(text, textpos)
                pygame.display.flip()
                pygame.quit()
                exit()

    pygame.display.update()
    sleep(0.7)
sleep(1)
f.close()
pygame.quit()
