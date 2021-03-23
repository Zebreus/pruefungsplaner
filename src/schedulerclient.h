#ifndef SCHEDULERCLIENT_H
#define SCHEDULERCLIENT_H

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QUuid>
#include <QWebSocket>

class SchedulerClient: public QObject {
  Q_OBJECT

  enum MessageId { StartScheduling = 1, RequestProgress = 2, GetResult = 3, ActivateSignals = 4 };

  inline static const int PROGRESS_UPDATE_FREQUENCY = 200;

  bool started;
  bool finished;

  QUrl schedulerUrl;
  QList<QString> initialMessages;
  QWebSocket schedulerSocket;
  QTimer updateRequestTimer;
  QUuid jobId;
  QString schedulingAlgorithm;

  float progress;
  QSharedPointer<QJsonObject> result;

 public:
  enum SchedulingMode { Fast = 1, Good = 2 };

 public:
  /**
   *  @brief Creates a SchedulerClient for scheduling plan in mode
   *  @param [in] url of the scheduler service
   *  @param [in] plan will be scheduled
   *  @param [in] mode sets the scheduling quality
   *  @param [in] parent is the parent of this QObject
   */
  explicit SchedulerClient(const QUrl& url, const QJsonObject& plan, SchedulingMode mode = Fast, QObject* parent = nullptr);
  /**
   *  @brief Creates a SchedulerClient for receiving updates about the job with
   * jobId
   *  @param [in] url of the scheduler server
   *  @param [in] jobId is the id of an existing job
   *  @param [in] parent is the parent of this QObject
   */
  explicit SchedulerClient(const QUrl& url, QUuid jobId, QObject* parent = nullptr);

  /**
   * @brief opens the connection to the scheduler service
   * If you call start scheduling before this,
   */
  void open();

  /**
   *  @brief Starts scheduling a plan or attaches to an existing plan
   */
  void startScheduling();

  /**
   * @brief Try to stop scheduling
   */
  void abortScheduling();

  float getProgress() const;

  QSharedPointer<QJsonObject> getResult() const;

 signals:
  /**
   * @brief Failed to connect to the scheduler service
   * @param message contains further detail
   */
  void connectionFailed(QString message);
  /**
   * @brief Failed to attach to existing job
   */
  void jobNotFound();
  /**
   * @brief Successfully started a scheduling or connected to one
   * @param jobId is the id of the scheduling
   */
  void schedulingStarted(QUuid jobId);
  /**
   * @brief Scheduling finished successfully
   * @param result is the scheduled plan
   */
  void schedulingComplete(QJsonObject result);
  /**
   * @brief Scheduling failed for some reason
   * @param message contains further detail
   */
  void schedulingFailed(QString errormessage);
  /**
   * @brief Scheduling emited a warning
   * @param message contains further detail
   */
  void warning(QString warning);
  /**
   * @brief The scheduling progress changed
   * @param progress is the current progress
   */
  void progressChanged(double progress);

 private Q_SLOTS:
  void onSocketError(QAbstractSocket::SocketError onError);
  void onConnected();
  void onTextMessageReceived(QString message);
  void onUpdateRequestTimer();

 private:
  /**
   *  @brief Creates a SchedulerClient that will connect to the given url
   *  @param [in] url of the scheduler server
   *  @param [in] parent is the parent of this QObject
   */
  explicit SchedulerClient(const QUrl& url, QObject* parent = nullptr);
  QString generateStopSchedulingMessage();
  QString generateActivateSignalsMessage();
  QString generateSetAlgorithmMessage(SchedulingMode mode);
  QString generateStartSchedulingMessage(const QJsonObject& plan, SchedulingMode mode);
  QString generateAttachSchedulingMessage(QUuid jobId);
  QString generateRequestProgressMessage();
  QString generateRequestResultMessage();
  void processMessage(const QJsonObject& message);
  void processResult(const QJsonObject& message);
  void processError(const QJsonObject& message);
  void processRequest(const QJsonObject& message);
  void stopScheduling();
};

#endif  // SCHEDULERCLIENT_H
