#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QGuiApplication>

#include <iostream>

struct OGL43CoreFormat : public QSurfaceFormat {
  OGL43CoreFormat() {
    setDepthBufferSize(24);
    setMajorVersion(4);
    setMinorVersion(3);
    setSamples(0);
    setOption(QSurfaceFormat::DebugContext);
    setProfile(QSurfaceFormat::CoreProfile);
    setAlphaBufferSize(8);
  }
};

struct OGL43CompatFormat : public QSurfaceFormat {
  OGL43CompatFormat() {
    setDepthBufferSize(24);
    setMajorVersion(4);
    setMinorVersion(3);
    setSamples(0);
    setOption(QSurfaceFormat::DebugContext);
    setProfile(QSurfaceFormat::CompatibilityProfile);
    setAlphaBufferSize(8);
  }
};

void createContext(QSurfaceFormat surfaceFormat){
    int argc = 0;
    QGuiApplication guiApp(argc, nullptr);

    QOffscreenSurface surface(QGuiApplication::primaryScreen());
    //!< set requested format for the offscreen surface
    surface.setFormat(surfaceFormat);
    //!< the creation converts the underlying format to the closest suppoted
    //!< by the current system
    surface.create();

    QOpenGLContext context(nullptr);
    context.setFormat(surfaceFormat);
    context.create();
    context.makeCurrent(&surface);

    std::cout << "QtOpenGLContextVersion: " +
                       std::to_string(context.format().version().first) +
                       std::to_string(context.format().version().second) 
                       << std::endl;
    std::cout.flush();

    //crash for compatibility profile
    context.versionFunctions()->initializeOpenGLFunctions();
}

int main() {

  createContext(OGL43CoreFormat());
  createContext(OGL43CompatFormat());

  return 0;
}

