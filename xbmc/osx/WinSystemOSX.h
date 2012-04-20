/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef WINDOW_SYSTEM_OSX_H
#define WINDOW_SYSTEM_OSX_H

#include "WinSystem.h"
#include "CriticalSection.h"
#include <SDL/SDL_video.h>

typedef uint32_t CGDirectDisplayID;
typedef u_int32_t CGDisplayChangeSummaryFlags;

class IDispResource;

class CWinSystemOSX : public CWinSystemBase
{
public:
  CWinSystemOSX();
  virtual ~CWinSystemOSX();

  // CWinSystemBase
  virtual bool InitWindowSystem();
  virtual bool DestroyWindowSystem();
  virtual bool CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool DestroyWindow();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void UpdateResolutions();
  virtual void NotifyAppFocusChange(bool bGaining);
  virtual void ShowOSMouse(bool show);
  virtual bool Minimize();
  virtual bool Restore();
  virtual bool Hide();
  virtual bool Show(bool raise = true);

  virtual void Register(IDispResource *resource);
  virtual void Unregister(IDispResource *resource);
  
  virtual void EnableSystemScreenSaver(bool bEnable);
  virtual bool IsSystemScreenSaverEnabled();
  
  virtual int GetNumScreens();
  virtual int GetCurrentScreen();
    
  virtual bool SwitchRefreshRate(float targetFPS, int screenID);
  virtual bool ResetDesktopRefreshRate();
  virtual void UpdateDisplayBlanking();

protected:
  void* CreateWindowedContext(void* shareCtx);
  void* CreateFullScreenContext(int screen_index, void* shareCtx);
  void  GetScreenResolution(int* w, int* h, double* fps);
  void  EnableVSync(bool enable);
  bool  SwitchToVideoMode(int width, int height, double refreshrate);
  void  GetVideoModes(void);
  bool  FlushBuffer(void);
  virtual size_t DisplayBitsPerPixelForMode(void *mode);
  
  void  CheckDisplayChanging(u_int32_t flags);
  static void DisplayReconfigured(CGDirectDisplayID display, CGDisplayChangeSummaryFlags flags, void *userData);

  void* m_glContext;
  static void* m_lastOwnedContext;
  SDL_Surface* m_SDLSurface;
    
  void* m_desktopVideoMode;
  int m_desktopScreenID;
  
  bool                         m_can_display_switch;
  
  CCriticalSection             m_resourceSection;
  std::vector<IDispResource*>  m_resources;
};

#endif // WINDOW_SYSTEM_H

