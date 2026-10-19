#pragma once

static const char kProvisionHtmlTemplate[] = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>%s Wi-Fi 配网</title>
  <style>
    :root {
      --bg: linear-gradient(160deg, #e7f7f3 0%%, #f7faf8 40%%, #d8ecff 100%%);
      --panel: rgba(255, 255, 255, 0.92);
      --ink: #17313b;
      --subtle: #5b7280;
      --accent: #147d64;
      --accent-2: #0b5ed7;
      --line: rgba(23, 49, 59, 0.12);
    }
    * { box-sizing: border-box; }
    body {
      margin: 0;
      min-height: 100vh;
      font-family: "Segoe UI", "PingFang SC", sans-serif;
      background: var(--bg);
      color: var(--ink);
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 20px;
    }
    .shell {
      width: min(760px, 100%%);
      background: var(--panel);
      backdrop-filter: blur(14px);
      border: 1px solid rgba(255,255,255,0.65);
      border-radius: 24px;
      box-shadow: 0 24px 60px rgba(16, 39, 56, 0.16);
      overflow: hidden;
    }
    .hero {
      padding: 28px 28px 18px;
      background: linear-gradient(135deg, rgba(20,125,100,0.12), rgba(11,94,215,0.10));
      border-bottom: 1px solid var(--line);
    }
    .hero-bar {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 12px;
      flex-wrap: wrap;
    }
    .eyebrow {
      display: inline-flex;
      align-items: center;
      gap: 8px;
      padding: 6px 12px;
      border-radius: 999px;
      background: rgba(20,125,100,0.12);
      color: var(--accent);
      font-size: 13px;
      font-weight: 700;
      letter-spacing: 0.04em;
      text-transform: uppercase;
    }
    .lang-switch {
      display: inline-flex;
      align-items: center;
      gap: 8px;
    }
    .lang-btn {
      appearance: none;
      border: 1px solid rgba(23,49,59,0.12);
      background: rgba(255,255,255,0.72);
      color: var(--ink);
      border-radius: 999px;
      padding: 8px 12px;
      font-size: 12px;
      font-weight: 700;
      cursor: pointer;
    }
    .lang-btn.active {
      background: var(--accent);
      border-color: var(--accent);
      color: white;
    }
    h1 {
      margin: 14px 0 8px;
      font-size: clamp(28px, 4vw, 40px);
      line-height: 1.05;
    }
    p {
      margin: 0;
      color: var(--subtle);
      line-height: 1.6;
    }
    .grid {
      display: grid;
      grid-template-columns: 1.05fr 0.95fr;
    }
    .pane {
      padding: 24px 28px 28px;
    }
    .pane + .pane {
      border-left: 1px solid var(--line);
    }
    .row {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 12px;
      margin-bottom: 12px;
    }
    .section-title {
      margin: 0;
      font-size: 16px;
      font-weight: 700;
    }
    .ghost {
      appearance: none;
      border: 1px solid rgba(11, 94, 215, 0.16);
      background: rgba(11, 94, 215, 0.07);
      color: var(--accent-2);
      border-radius: 999px;
      padding: 10px 14px;
      font-weight: 700;
      cursor: pointer;
    }
    .hint {
      margin-bottom: 14px;
      font-size: 13px;
      color: var(--subtle);
    }
    .list {
      display: grid;
      gap: 10px;
      max-height: 320px;
      overflow: auto;
      padding-right: 2px;
    }
    .network {
      appearance: none;
      width: 100%%;
      border: 1px solid var(--line);
      border-radius: 16px;
      background: white;
      padding: 14px 16px;
      text-align: left;
      cursor: pointer;
      transition: transform 120ms ease, box-shadow 120ms ease, border-color 120ms ease;
    }
    .network:active {
      transform: scale(0.99);
    }
    .network:hover {
      border-color: rgba(20,125,100,0.34);
      box-shadow: 0 10px 24px rgba(20,125,100,0.10);
    }
    .network strong {
      display: block;
      font-size: 15px;
      color: var(--ink);
    }
    .network span {
      display: block;
      margin-top: 4px;
      font-size: 12px;
      color: var(--subtle);
    }
    .status {
      margin-bottom: 12px;
      font-size: 13px;
      color: var(--subtle);
    }
    .empty {
      padding: 18px;
      border: 1px dashed var(--line);
      border-radius: 16px;
      color: var(--subtle);
      background: rgba(255,255,255,0.55);
    }
    form {
      display: grid;
      gap: 14px;
    }
    label {
      display: block;
      font-size: 13px;
      font-weight: 700;
      margin-bottom: 6px;
    }
    input {
      width: 100%%;
      border: 1px solid var(--line);
      border-radius: 14px;
      padding: 13px 14px;
      font-size: 16px;
      background: rgba(255,255,255,0.95);
    }
    select {
      width: 100%%;
      border: 1px solid var(--line);
      border-radius: 14px;
      padding: 13px 14px;
      font-size: 16px;
      background: rgba(255,255,255,0.95);
    }
    .submit {
      appearance: none;
      border: 0;
      border-radius: 14px;
      padding: 14px 16px;
      background: linear-gradient(135deg, #147d64, #0b5ed7);
      color: white;
      font-size: 16px;
      font-weight: 800;
      letter-spacing: 0.01em;
      cursor: pointer;
      box-shadow: 0 14px 26px rgba(11,94,215,0.18);
    }
    .device {
      margin-top: 14px;
      padding: 12px 14px;
      border-radius: 14px;
      background: rgba(23,49,59,0.05);
      font-size: 13px;
      color: var(--subtle);
    }
    .device strong {
      color: var(--ink);
    }
    .link-value {
      color: var(--accent-2);
      text-decoration: none;
      font-weight: 700;
    }
    .link-value:hover {
      text-decoration: underline;
    }
    .config-panel {
      border-top: 1px solid var(--line);
      padding: 24px 28px 28px;
      background: rgba(255,255,255,0.54);
    }
    .dashboard {
      border-top: 1px solid var(--line);
      padding: 24px 28px 30px;
      background: rgba(255,255,255,0.46);
    }
    .status-head {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 12px;
      margin-bottom: 14px;
      flex-wrap: wrap;
    }
    .updated {
      font-size: 12px;
      color: var(--subtle);
    }
    .metrics {
      display: grid;
      grid-template-columns: repeat(4, minmax(0, 1fr));
      gap: 10px;
      margin-bottom: 14px;
    }
    .metric {
      border: 1px solid var(--line);
      border-radius: 12px;
      padding: 12px;
      background: rgba(255,255,255,0.82);
      min-width: 0;
    }
    .metric span {
      display: block;
      color: var(--subtle);
      font-size: 12px;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
    }
    .metric strong {
      display: block;
      margin-top: 5px;
      font-size: 19px;
      line-height: 1.1;
      overflow-wrap: anywhere;
    }
    .status-grid {
      display: grid;
      grid-template-columns: repeat(3, minmax(0, 1fr));
      gap: 10px;
    }
    .status-panel {
      border: 1px solid var(--line);
      border-radius: 12px;
      padding: 12px;
      background: rgba(255,255,255,0.82);
      min-width: 0;
    }
    .status-panel h3 {
      margin: 0 0 10px;
      font-size: 14px;
    }
    .status-panel form {
      margin-top: 10px;
      gap: 10px;
    }
    .kv {
      display: flex;
      justify-content: space-between;
      gap: 10px;
      padding: 5px 0;
      border-top: 1px solid rgba(23,49,59,0.07);
      font-size: 12px;
    }
    .kv:first-of-type { border-top: 0; }
    .kv span {
      color: var(--subtle);
      white-space: nowrap;
    }
    .kv strong {
      text-align: right;
      overflow-wrap: anywhere;
    }
    .bar {
      height: 8px;
      border-radius: 999px;
      background: rgba(23,49,59,0.10);
      overflow: hidden;
      margin-top: 8px;
    }
    .bar i {
      display: block;
      height: 100%%;
      width: 0%%;
      background: linear-gradient(90deg, #147d64, #0b5ed7);
      border-radius: inherit;
      transition: width 180ms ease;
    }
    @media (max-width: 720px) {
      .grid { grid-template-columns: 1fr; }
      .pane + .pane { border-left: 0; border-top: 1px solid var(--line); }
      .hero, .pane { padding-left: 20px; padding-right: 20px; }
      .config-panel { padding-left: 20px; padding-right: 20px; }
      .dashboard { padding-left: 20px; padding-right: 20px; }
      .metrics { grid-template-columns: repeat(2, minmax(0, 1fr)); }
      .status-grid { grid-template-columns: 1fr; }
    }
  </style>
</head>
<body>
  <main class="shell">
    <section class="hero">
      <div class="hero-bar">
        <div id="portal-badge" class="eyebrow">配网门户已启用</div>
        <div class="lang-switch">
          <button id="lang-zh" class="lang-btn active" type="button">中文</button>
          <button id="lang-en" class="lang-btn" type="button">EN</button>
        </div>
      </div>
      <h1 id="hero-title" data-device-name="%s">正在为设备连接 Wi-Fi</h1>
      <p id="hero-desc">请保持连接当前热点。你可以从扫描结果中选择 Wi-Fi，也可以手动输入，保存后设备会自动重启并连接目标网络。</p>
    </section>
    <section class="grid">
      <div class="pane">
        <div class="row">
          <h2 id="nearby-title" class="section-title">附近 Wi-Fi</h2>
          <button id="scan-btn" class="ghost" type="button">重新扫描</button>
        </div>
        <div id="scan-status" class="status">正在扫描附近 Wi-Fi...</div>
        <div id="network-list" class="list">
          <div id="network-empty" class="empty">扫描结果会显示在这里。</div>
        </div>
      </div>
      <div class="pane">
        <div id="hint-text" class="hint">如果没有自动弹出配网页，请在连接当前热点后手动打开 <strong>http://192.168.4.1</strong>。</div>
        <form method="post" action="/api/provision">
          <input id="lang-input" name="lang" type="hidden" value="zh">
          <div>
            <label id="ssid-label" for="ssid">Wi-Fi 名称</label>
            <input id="ssid" name="ssid" maxlength="32" autocomplete="off" required>
          </div>
          <div>
            <label id="password-label" for="password">密码</label>
            <input id="password" name="password" maxlength="64" type="password" placeholder="开放网络可留空">
          </div>
          <button id="submit-btn" class="submit" type="submit">保存并重启</button>
        </form>
        <div id="device-label" class="device" data-device-name="%s">热点名称：<strong>%s</strong></div>
      </div>
    </section>
    <section class="config-panel">
      <div class="row">
        <h2 id="runtime-title" class="section-title">通信设置</h2>
        <div id="runtime-status" class="updated">加载中...</div>
      </div>
      <form id="runtime-form">
        <div>
          <label id="comm-mode-label" for="comm-mode">默认通信协议</label>
          <select id="comm-mode" name="comm_mode">
            <option value="micro_ros">micro-ROS</option>
            <option value="microros_uart">micro-ROS UART</option>
            <option value="mavlink_udp">MAVLink UDP</option>
            <option value="uart_mavlink">MAVLink UART</option>
          </select>
        </div>
        <div>
          <label id="agent-ip-label" for="agent-ip">micro-ROS Agent IP</label>
          <input id="agent-ip" name="microros_agent_ip" maxlength="15" inputmode="decimal" required>
        </div>
        <div>
          <label id="agent-port-label" for="agent-port">micro-ROS Agent Port</label>
          <input id="agent-port" name="microros_agent_port" type="number" min="1" max="65535" required>
        </div>
        <button id="runtime-submit-btn" class="submit" type="submit">保存通信设置并重启</button>
      </form>
    </section>
    <section class="dashboard">
      <div class="status-head">
        <h2 id="status-title" class="section-title">设备状态</h2>
        <div id="status-updated" class="updated">等待状态数据...</div>
      </div>
      <div class="metrics">
        <div class="metric"><span id="metric-device-label">设备</span><strong id="metric-device">--</strong></div>
        <div class="metric"><span id="metric-wifi-label">Wi-Fi</span><strong id="metric-wifi">--</strong></div>
        <div class="metric"><span id="metric-temp-label">温度</span><strong id="metric-temp">--</strong></div>
        <div class="metric"><span id="metric-uptime-label">运行时间</span><strong id="metric-uptime">--</strong></div>
      </div>
      <div class="status-grid">
        <div class="status-panel">
          <h3 id="panel-system-title">系统</h3>
          <div class="kv"><span>Heap</span><strong id="stat-heap">--</strong></div>
          <div class="bar"><i id="bar-heap"></i></div>
          <div class="kv"><span>Flash</span><strong id="stat-flash">--</strong></div>
          <div class="bar"><i id="bar-flash"></i></div>
          <div class="kv"><span>Emergency</span><strong id="stat-emergency">--</strong></div>
          <div class="kv"><span>Motion Busy</span><strong id="stat-busy">--</strong></div>
        </div>
        <div class="status-panel">
          <h3 id="panel-imu-title">IMU</h3>
          <div class="kv"><span>Roll</span><strong id="stat-roll">--</strong></div>
          <div class="kv"><span>Pitch</span><strong id="stat-pitch">--</strong></div>
          <div class="kv"><span>Yaw</span><strong id="stat-yaw">--</strong></div>
          <div class="kv"><span>Accel</span><strong id="stat-accel">--</strong></div>
          <div class="kv"><span>Gyro</span><strong id="stat-gyro">--</strong></div>
        </div>
        <div class="status-panel">
          <h3 id="panel-motion-title">运动</h3>
          <div class="kv"><span>Velocity</span><strong id="stat-velocity">--</strong></div>
          <div class="kv"><span>Position</span><strong id="stat-position">--</strong></div>
          <div class="kv"><span>Wheel</span><strong id="stat-wheel">--</strong></div>
          <div class="kv"><span>Target</span><strong id="stat-target">--</strong></div>
          <div class="kv"><span>Mode</span><strong id="stat-motion-mode">--</strong></div>
        </div>
        <div class="status-panel">
          <h3 id="panel-sensor-title">传感器</h3>
          <div class="kv"><span>Ultrasonic</span><strong id="stat-ultrasonic">--</strong></div>
          <div class="kv"><span>Lidar</span><strong id="stat-lidar">--</strong></div>
          <div class="kv"><span>Gamepad</span><strong id="stat-gamepad">--</strong></div>
          <div class="kv"><span>Battery</span><strong id="stat-battery">--</strong></div>
        </div>
      <div class="status-panel">
        <h3 id="panel-wifi-title">网络</h3>
        <div class="kv"><span>Mode</span><strong id="stat-wifi-mode">--</strong></div>
        <div class="kv"><span>SSID</span><strong id="stat-wifi-ssid">--</strong></div>
        <div class="kv"><span>RSSI</span><strong id="stat-wifi-rssi">--</strong></div>
        <div class="kv"><span>AP IP</span><strong id="stat-ap-ip">--</strong></div>
        <div class="kv"><span>主机 Hostname</span><strong id="stat-hostname">--</strong></div>
        <div class="kv"><span>主机 IP</span><strong id="stat-hostip">--</strong></div>
      </div>
        <div class="status-panel">
          <h3 id="panel-camera-title">摄像头</h3>
          <div class="kv"><span>State</span><strong id="stat-camera-state">--</strong></div>
          <div class="kv"><span>Name</span><strong id="stat-camera-name">--</strong></div>
          <div class="kv"><span>IP</span><strong id="stat-camera-ip">--</strong></div>
          <div class="kv"><span>Config</span><strong id="stat-camera-config">--</strong></div>
          <div class="kv"><span>Stream</span><strong id="stat-camera-stream">--</strong></div>
          <form id="camera-form">
            <div>
              <label id="camera-ssid-label" for="camera-ssid">摄像头 Wi-Fi 名称</label>
              <input id="camera-ssid" name="ssid" maxlength="32" autocomplete="off" required>
            </div>
            <div>
              <label id="camera-password-label" for="camera-password">摄像头 Wi-Fi 密码</label>
              <input id="camera-password" name="password" maxlength="64" type="password" placeholder="开放网络可留空">
            </div>
            <div>
              <label id="camera-command-label" for="camera-command">配网命令格式</label>
              <select id="camera-command" name="format">
                <option value="wifi">WIFI:ssid,password</option>
                <option value="set_wifi">SET_WIFI:ssid,password</option>
                <option value="prov">PROV:ssid|password</option>
                <option value="json">{"ssid":"xxx","password":"yyy"}</option>
              </select>
            </div>
            <button id="camera-submit-btn" class="submit" type="submit">发送摄像头配网</button>
            <div id="camera-status" class="updated">等待摄像头状态...</div>
          </form>
        </div>
        <div class="status-panel">
          <h3 id="panel-pid-title">PID</h3>
          <div class="kv"><span>Speed</span><strong id="stat-pid-speed">--</strong></div>
          <div class="kv"><span>Position</span><strong id="stat-pid-position">--</strong></div>
        </div>
      </div>
    </section>
  </main>
  <script>
    const scanButton = document.getElementById('scan-btn');
    const langZhButton = document.getElementById('lang-zh');
    const langEnButton = document.getElementById('lang-en');
    const scanStatus = document.getElementById('scan-status');
    const networkList = document.getElementById('network-list');
    const langInput = document.getElementById('lang-input');
    const ssidInput = document.getElementById('ssid');
    const passwordInput = document.getElementById('password');
    const runtimeForm = document.getElementById('runtime-form');
    const commModeInput = document.getElementById('comm-mode');
    const agentIpInput = document.getElementById('agent-ip');
    const agentPortInput = document.getElementById('agent-port');
    const cameraForm = document.getElementById('camera-form');
    const cameraSsidInput = document.getElementById('camera-ssid');
    const cameraPasswordInput = document.getElementById('camera-password');
    const cameraCommandInput = document.getElementById('camera-command');
    const heroTitle = document.getElementById('hero-title');
    const deviceLabel = document.getElementById('device-label');
    const deviceName = heroTitle.dataset.deviceName || deviceLabel.dataset.deviceName || '';
    let currentLanguage = 'zh';
    let runtimeFormDirty = false;

    const translations = {
      zh: {
        documentTitle: `${deviceName} Wi-Fi 配网`,
        htmlLang: 'zh-CN',
        portalBadge: '配网门户已启用',
        heroTitle: `正在为 ${deviceName} 连接 Wi-Fi`,
        heroDesc: '请保持连接当前热点。你可以从扫描结果中选择 Wi-Fi，也可以手动输入，保存后设备会自动重启并连接目标网络。',
        nearbyTitle: '附近 Wi-Fi',
        scanAgain: '重新扫描',
        scanPending: '正在扫描附近 Wi-Fi...',
        emptyInitial: '扫描结果会显示在这里。',
        emptyNoNetworks: '没有扫描到可用 Wi-Fi。请让设备更靠近路由器后重试。',
        emptyScanFailed: 'Wi-Fi 扫描失败，请点击“重新扫描”再试一次。',
        hintHtml: '如果没有自动弹出配网页，请在连接当前热点后手动打开 <strong>http://192.168.4.1</strong>。',
        ssidLabel: 'Wi-Fi 名称',
        passwordLabel: '密码',
        passwordPlaceholder: '开放网络可留空',
        submit: '保存并重启',
        deviceHtml: `热点名称：<strong>${deviceName}</strong>`,
        foundStatus: (count) => `已发现 ${count} 个 Wi-Fi，点击任意一项可自动填入名称。`,
        scanFailedStatus: (message) => `扫描失败：${message}`,
        signalExcellent: '信号极强',
        signalStrong: '信号良好',
        signalFair: '信号一般',
        signalWeak: '信号较弱',
        authOpen: '开放网络',
        hiddenSsid: '(隐藏 SSID)',
        statusTitle: '设备状态',
        statusWaiting: '等待状态数据...',
        statusUpdated: (time) => `已更新 ${time}`,
        statusFailed: (message) => `状态读取失败：${message}`,
        runtimeTitle: '通信设置',
        runtimeLoading: '加载中...',
        runtimeSaved: '已保存，设备正在重启...',
        runtimeSaveFailed: (message) => `保存失败：${message}`,
        commModeLabel: '默认通信协议',
        agentIpLabel: 'micro-ROS Agent IP',
        agentPortLabel: 'micro-ROS Agent Port',
        runtimeSubmit: '保存通信设置并重启',
        cameraProvisionSaved: '摄像头配网命令已发送，等待摄像头重启或更新状态...',
        cameraProvisionFailed: (message) => `摄像头配网失败：${message}`,
        cameraSsidLabel: '摄像头 Wi-Fi 名称',
        cameraPasswordLabel: '摄像头 Wi-Fi 密码',
        cameraCommandLabel: '配网命令格式',
        cameraSubmit: '发送摄像头配网',
        cameraWaiting: '等待摄像头状态...',
        metricDevice: '设备',
        metricWifi: 'Wi-Fi',
        metricTemp: '温度',
        metricUptime: '运行时间',
        panelSystem: '系统',
        panelImu: 'IMU',
        panelMotion: '运动',
        panelSensor: '传感器',
        panelWifi: '网络',
        panelCamera: '摄像头',
        panelPid: 'PID',
        connected: '已连接',
        disconnected: '未连接',
        valid: '有效',
        invalid: '无数据',
        open: '打开',
        yes: '是',
        no: '否',
      },
      en: {
        documentTitle: `${deviceName} Wi-Fi Setup`,
        htmlLang: 'en',
        portalBadge: 'Captive Portal Active',
        heroTitle: `Connect ${deviceName} to Wi-Fi`,
        heroDesc: 'Stay connected to this hotspot. Choose a Wi-Fi network from the scan list or enter one manually, then save. The device will restart and join the selected network.',
        nearbyTitle: 'Nearby Wi-Fi',
        scanAgain: 'Scan Again',
        scanPending: 'Scanning nearby Wi-Fi...',
        emptyInitial: 'Scan results will appear here.',
        emptyNoNetworks: 'No Wi-Fi networks were found. Move the device closer to the router and scan again.',
        emptyScanFailed: 'Wi-Fi scan failed. Tap "Scan Again" to retry.',
        hintHtml: 'If the portal page does not open automatically, connect to this hotspot and manually open <strong>http://192.168.4.1</strong>.',
        ssidLabel: 'Wi-Fi Name',
        passwordLabel: 'Password',
        passwordPlaceholder: 'Leave empty for open networks',
        submit: 'Save and Restart',
        deviceHtml: `Hotspot name: <strong>${deviceName}</strong>`,
        foundStatus: (count) => `Found ${count} networks. Tap one to fill the SSID.`,
        scanFailedStatus: (message) => `Scan failed: ${message}`,
        signalExcellent: 'Excellent',
        signalStrong: 'Strong',
        signalFair: 'Fair',
        signalWeak: 'Weak',
        authOpen: 'Open',
        hiddenSsid: '(Hidden SSID)',
        statusTitle: 'Device Status',
        statusWaiting: 'Waiting for status data...',
        statusUpdated: (time) => `Updated ${time}`,
        statusFailed: (message) => `Status failed: ${message}`,
        runtimeTitle: 'Communication Settings',
        runtimeLoading: 'Loading...',
        runtimeSaved: 'Saved. Device is restarting...',
        runtimeSaveFailed: (message) => `Save failed: ${message}`,
        commModeLabel: 'Default Protocol',
        agentIpLabel: 'micro-ROS Agent IP',
        agentPortLabel: 'micro-ROS Agent Port',
        runtimeSubmit: 'Save Settings and Restart',
        cameraProvisionSaved: 'Camera provisioning command sent. Waiting for the camera to restart or update status...',
        cameraProvisionFailed: (message) => `Camera provisioning failed: ${message}`,
        cameraSsidLabel: 'Camera Wi-Fi Name',
        cameraPasswordLabel: 'Camera Wi-Fi Password',
        cameraCommandLabel: 'Provision Command Format',
        cameraSubmit: 'Send Camera Provisioning',
        cameraWaiting: 'Waiting for camera status...',
        metricDevice: 'Device',
        metricWifi: 'Wi-Fi',
        metricTemp: 'Temp',
        metricUptime: 'Uptime',
        panelSystem: 'System',
        panelImu: 'IMU',
        panelMotion: 'Motion',
        panelSensor: 'Sensors',
        panelWifi: 'Network',
        panelCamera: 'Camera',
        panelPid: 'PID',
        connected: 'Connected',
        disconnected: 'Disconnected',
        valid: 'Valid',
        invalid: 'No Data',
        open: 'Open',
        yes: 'Yes',
        no: 'No',
      }
    };

    function getI18n() {
      return translations[currentLanguage] || translations.zh;
    }

    function setProvisionLanguage(lang) {
      currentLanguage = translations[lang] ? lang : 'zh';
      const i18n = getI18n();

      document.documentElement.lang = i18n.htmlLang;
      document.title = i18n.documentTitle;
      document.getElementById('portal-badge').textContent = i18n.portalBadge;
      heroTitle.textContent = i18n.heroTitle;
      document.getElementById('hero-desc').textContent = i18n.heroDesc;
      document.getElementById('nearby-title').textContent = i18n.nearbyTitle;
      scanButton.textContent = i18n.scanAgain;
      document.getElementById('hint-text').innerHTML = i18n.hintHtml;
      document.getElementById('ssid-label').textContent = i18n.ssidLabel;
      document.getElementById('password-label').textContent = i18n.passwordLabel;
      passwordInput.placeholder = i18n.passwordPlaceholder;
      document.getElementById('submit-btn').textContent = i18n.submit;
      deviceLabel.innerHTML = i18n.deviceHtml;
      langInput.value = currentLanguage;
      document.getElementById('status-title').textContent = i18n.statusTitle;
      document.getElementById('runtime-title').textContent = i18n.runtimeTitle;
      document.getElementById('comm-mode-label').textContent = i18n.commModeLabel;
      document.getElementById('agent-ip-label').textContent = i18n.agentIpLabel;
      document.getElementById('agent-port-label').textContent = i18n.agentPortLabel;
      document.getElementById('runtime-submit-btn').textContent = i18n.runtimeSubmit;
      document.getElementById('camera-ssid-label').textContent = i18n.cameraSsidLabel;
      document.getElementById('camera-password-label').textContent = i18n.cameraPasswordLabel;
      document.getElementById('camera-command-label').textContent = i18n.cameraCommandLabel;
      document.getElementById('camera-submit-btn').textContent = i18n.cameraSubmit;
      cameraPasswordInput.placeholder = i18n.passwordPlaceholder;
      document.getElementById('metric-device-label').textContent = i18n.metricDevice;
      document.getElementById('metric-wifi-label').textContent = i18n.metricWifi;
      document.getElementById('metric-temp-label').textContent = i18n.metricTemp;
      document.getElementById('metric-uptime-label').textContent = i18n.metricUptime;
      document.getElementById('panel-system-title').textContent = i18n.panelSystem;
      document.getElementById('panel-imu-title').textContent = i18n.panelImu;
      document.getElementById('panel-motion-title').textContent = i18n.panelMotion;
      document.getElementById('panel-sensor-title').textContent = i18n.panelSensor;
      document.getElementById('panel-wifi-title').textContent = i18n.panelWifi;
      document.getElementById('panel-camera-title').textContent = i18n.panelCamera;
      document.getElementById('panel-pid-title').textContent = i18n.panelPid;

      langZhButton.classList.toggle('active', currentLanguage === 'zh');
      langEnButton.classList.toggle('active', currentLanguage === 'en');

      const url = new URL(window.location.href);
      url.searchParams.set('lang', currentLanguage);
      window.history.replaceState({}, '', url.toString());
    }

    function signalLabel(rssi) {
      const i18n = getI18n();
      if (rssi >= -55) return i18n.signalExcellent;
      if (rssi >= -67) return i18n.signalStrong;
      if (rssi >= -75) return i18n.signalFair;
      return i18n.signalWeak;
    }

    function pickNetwork(ssid) {
      ssidInput.value = ssid;
      cameraSsidInput.value = ssid;
      passwordInput.focus();
    }

    function renderNetworks(networks) {
      const i18n = getI18n();
      if (!Array.isArray(networks) || networks.length === 0) {
        networkList.innerHTML = `<div class="empty">${i18n.emptyNoNetworks}</div>`;
        return;
      }

      networkList.innerHTML = '';
      networks.forEach((network) => {
        const button = document.createElement('button');
        button.type = 'button';
        button.className = 'network';
        button.addEventListener('click', () => pickNetwork(network.ssid));

        const title = document.createElement('strong');
        title.textContent = network.ssid || i18n.hiddenSsid;
        button.appendChild(title);

        const meta = document.createElement('span');
        const auth = network.open ? i18n.authOpen : network.auth;
        meta.textContent = `${auth} | RSSI ${network.rssi} dBm | ${signalLabel(network.rssi)}`;
        button.appendChild(meta);

        networkList.appendChild(button);
      });
    }

    async function scanNetworks() {
      const i18n = getI18n();
      scanButton.disabled = true;
      scanStatus.textContent = i18n.scanPending;
      try {
        const response = await fetch('/api/scan', { cache: 'no-store' });
        if (!response.ok) {
          throw new Error(`HTTP ${response.status}`);
        }
        const payload = await response.json();
        renderNetworks(payload.networks || []);
        scanStatus.textContent = i18n.foundStatus(payload.networks ? payload.networks.length : 0);
      } catch (error) {
        networkList.innerHTML = `<div class="empty">${i18n.emptyScanFailed}</div>`;
        scanStatus.textContent = i18n.scanFailedStatus(error.message);
      } finally {
        scanButton.disabled = false;
      }
    }

    function text(id, value) {
      const node = document.getElementById(id);
      if (node) node.textContent = value;
    }

    function link(id, url) {
      const node = document.getElementById(id);
      if (!node) return;
      if (!url) {
        node.textContent = '--';
        return;
      }
      node.innerHTML = '';
      const anchor = document.createElement('a');
      anchor.className = 'link-value';
      anchor.href = url;
      anchor.target = '_blank';
      anchor.rel = 'noopener noreferrer';
      anchor.textContent = getI18n().open;
      node.appendChild(anchor);
    }

    function pct(value, total) {
      if (!total || total <= 0) return 0;
      return Math.max(0, Math.min(100, Math.round((value / total) * 100)));
    }

    function setBar(id, percent) {
      const node = document.getElementById(id);
      if (node) node.style.width = `${Math.max(0, Math.min(100, percent))}%%`;
    }

    function fixed(value, digits = 1) {
      return Number.isFinite(value) ? Number(value).toFixed(digits) : '--';
    }

    function formatBool(value) {
      const i18n = getI18n();
      return value ? i18n.yes : i18n.no;
    }

    function formatUptime(ms) {
      if (!Number.isFinite(ms)) return '--';
      const totalSeconds = Math.floor(ms / 1000);
      const hours = Math.floor(totalSeconds / 3600);
      const minutes = Math.floor((totalSeconds %% 3600) / 60);
      const seconds = totalSeconds %% 60;
      if (hours > 0) return `${hours}h ${minutes}m`;
      if (minutes > 0) return `${minutes}m ${seconds}s`;
      return `${seconds}s`;
    }

    function pidLine(pid) {
      if (!pid) return '--';
      return `${fixed(pid.kp, 2)} / ${fixed(pid.ki, 2)} / ${fixed(pid.kd, 2)}`;
    }

    function renderStatus(data) {
      const i18n = getI18n();
      const wifi = data.wifi || {};
      const memory = data.memory || {};
      const storage = data.storage || {};
      const temperature = data.temperature || {};
      const imu = data.imu || {};
      const motion = data.motion || {};
      const ultrasonic = data.ultrasonic || {};
      const lidar = data.lidar || {};
      const gamepad = data.gamepad || {};
      const battery = data.battery || {};
      const pid = data.pid || {};
      const runtime = data.runtime || {};
      const camera = data.camera || {};
      const targetHost = data.target_host || {};

      text('metric-device', data.device_name || '--');
      text('metric-wifi', wifi.sta_connected ? i18n.connected : `${wifi.mode || '--'}`);
      text('metric-temp', temperature.valid ? `${fixed(temperature.celsius, 1)} C` : '--');
      text('metric-uptime', formatUptime(data.uptime_ms));
      text('status-updated', i18n.statusUpdated(new Date().toLocaleTimeString()));

      const heapPercent = pct(memory.heap_used_kib, memory.heap_total_kib);
      text('stat-heap', `${memory.heap_used_kib || 0}/${memory.heap_total_kib || 0} KiB (${heapPercent}%%)`);
      setBar('bar-heap', heapPercent);
      const flashPercent = pct(storage.partition_used_kib, storage.flash_total_kib);
      text('stat-flash', `${storage.partition_used_kib || 0}/${storage.flash_total_kib || 0} KiB (${flashPercent}%%)`);
      setBar('bar-flash', flashPercent);
      text('stat-emergency', formatBool(data.emergency_stop));
      text('stat-busy', formatBool(data.motion_busy));

      text('stat-roll', imu.valid ? `${fixed(imu.roll, 1)} deg` : i18n.invalid);
      text('stat-pitch', imu.valid ? `${fixed(imu.pitch, 1)} deg` : i18n.invalid);
      text('stat-yaw', imu.valid ? `${fixed(imu.yaw, 1)} deg` : i18n.invalid);
      text('stat-accel', imu.valid ? `${fixed(imu.acc_x, 2)}, ${fixed(imu.acc_y, 2)}, ${fixed(imu.acc_z, 2)} g` : i18n.invalid);
      text('stat-gyro', imu.valid ? `${fixed(imu.gyro_x, 1)}, ${fixed(imu.gyro_y, 1)}, ${fixed(imu.gyro_z, 1)} dps` : i18n.invalid);

      text('stat-velocity', motion.valid ? `${fixed(motion.vx, 0)}, ${fixed(motion.vy, 0)} mm/s | ${fixed(motion.wz, 2)} rad/s` : i18n.invalid);
      text('stat-position', motion.valid ? `${fixed(motion.x, 0)}, ${fixed(motion.y, 0)} mm | ${fixed(motion.yaw, 1)} deg` : i18n.invalid);
      text('stat-wheel', motion.valid ? `${fixed(motion.vel_left, 0)} / ${fixed(motion.vel_right, 0)} mm/s` : i18n.invalid);
      text('stat-target', motion.valid ? `${fixed(motion.target_vx, 0)}, ${fixed(motion.target_vy, 0)} | ${fixed(motion.target_wz, 2)}` : i18n.invalid);
      text('stat-motion-mode', motion.valid ? `${motion.control_mode} / src ${motion.source}` : i18n.invalid);

      text('stat-ultrasonic', ultrasonic.valid ? `${fixed(ultrasonic.distance_cm, 1)} cm | ${ultrasonic.obstacle ? 'OBS' : 'clear'}` : i18n.invalid);
      text('stat-lidar', lidar.valid ? `${lidar.valid_points} pts | ${lidar.min_mm}-${lidar.max_mm} mm` : i18n.invalid);
      text('stat-gamepad', gamepad.valid ? `${gamepad.connected ? i18n.connected : i18n.disconnected} | ${gamepad.left_x},${gamepad.left_y} / ${gamepad.right_x},${gamepad.right_y}` : i18n.invalid);
      text('stat-battery', battery.valid ? `${fixed(battery.voltage_v, 2)} V | ${battery.percentage}%% | ADC ${fixed(battery.adc_voltage_v, 3)} V` : i18n.invalid);

      text('stat-wifi-mode', wifi.mode || '--');
      text('stat-wifi-ssid', wifi.ssid || '--');
      text('stat-wifi-rssi', Number.isFinite(wifi.rssi) ? `${wifi.rssi} dBm` : '--');
      text('stat-ap-ip', wifi.ap_ip || '--');
      text('stat-hostname', targetHost.valid ? (targetHost.hostname || '--') : '--');
      text('stat-hostip', targetHost.valid ? (targetHost.hostip || '--') : '--');

      text('stat-camera-state', camera.reachable ? (camera.valid ? i18n.connected : i18n.invalid) : i18n.disconnected);
      text('stat-camera-name', camera.name || '--');
      text('stat-camera-ip', camera.ip || '--');
      link('stat-camera-config', camera.config_url);
      link('stat-camera-stream', camera.stream_url);
      text('camera-status', camera.reachable ? `${camera.mode || '--'} | ${camera.ip || '--'}` : (camera.error || i18n.disconnected));

      text('stat-pid-speed', pidLine(pid.speed));
      text('stat-pid-position', pidLine(pid.position));

      if (!runtimeFormDirty) {
        if (runtime.comm_mode) commModeInput.value = runtime.comm_mode;
        if (runtime.microros_agent_ip) agentIpInput.value = runtime.microros_agent_ip;
        if (runtime.microros_agent_port) agentPortInput.value = runtime.microros_agent_port;
      }
      text('runtime-status', `${runtime.comm_mode || '--'} | ${runtime.microros_agent_ip || '--'}:${runtime.microros_agent_port || '--'}`);
    }

    async function refreshStatus() {
      try {
        const response = await fetch('/api/status', { cache: 'no-store' });
        if (!response.ok) {
          throw new Error(`HTTP ${response.status}`);
        }
        renderStatus(await response.json());
      } catch (error) {
        text('status-updated', getI18n().statusFailed(error.message));
      }
    }

    window.setProvisionLanguage = setProvisionLanguage;
    langZhButton.addEventListener('click', () => setProvisionLanguage('zh'));
    langEnButton.addEventListener('click', () => setProvisionLanguage('en'));
    scanButton.addEventListener('click', scanNetworks);
    runtimeForm.addEventListener('input', () => {
      runtimeFormDirty = true;
    });
    runtimeForm.addEventListener('submit', async (event) => {
      event.preventDefault();
      const i18n = getI18n();
      const body = new URLSearchParams();
      body.set('comm_mode', commModeInput.value);
      body.set('microros_agent_ip', agentIpInput.value.trim());
      body.set('microros_agent_port', agentPortInput.value.trim());
      try {
        const response = await fetch('/api/runtime-config', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body
        });
        if (!response.ok) {
          throw new Error(await response.text() || `HTTP ${response.status}`);
        }
        runtimeFormDirty = false;
        text('runtime-status', i18n.runtimeSaved);
      } catch (error) {
        text('runtime-status', i18n.runtimeSaveFailed(error.message));
      }
    });
    cameraForm.addEventListener('submit', async (event) => {
      event.preventDefault();
      const i18n = getI18n();
      const body = new URLSearchParams();
      body.set('ssid', cameraSsidInput.value.trim());
      body.set('password', cameraPasswordInput.value);
      body.set('format', cameraCommandInput.value);
      try {
        const response = await fetch('/api/camera/provision', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body
        });
        if (!response.ok) {
          throw new Error(await response.text() || `HTTP ${response.status}`);
        }
        text('camera-status', i18n.cameraProvisionSaved);
        refreshStatus();
      } catch (error) {
        text('camera-status', i18n.cameraProvisionFailed(error.message));
      }
    });
    window.addEventListener('load', () => {
      const lang = new URLSearchParams(window.location.search).get('lang');
      setProvisionLanguage(lang === 'en' ? 'en' : 'zh');
      document.getElementById('network-empty').textContent = getI18n().emptyInitial;
      document.getElementById('camera-status').textContent = getI18n().cameraWaiting;
      scanNetworks();
      refreshStatus();
      setInterval(refreshStatus, 1000);
    });
  </script>
</body>
</html>
)HTML";
