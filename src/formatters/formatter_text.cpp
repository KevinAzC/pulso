std::string FormatterText::formatear(
    const chuspapulse::core::Snapshot& snapshot
) const {
    // Extraer métricas del snapshot
    double cpu_pct = 0.0;
    double ram_usado_bytes = 0.0;
    double ram_total_bytes = 0.0;
    double disco_usado_bytes = 0.0;
    double disco_total_bytes = 0.0;
    double net_rx_bytes = 0.0;
    double net_tx_bytes = 0.0;

    for (const auto& metrica : snapshot.metricas) {
        if (metrica.nombre == "cpu.usage" || metrica.nombre == "cpu") {
            cpu_pct = metrica.valor;
        } else if (metrica.nombre == "ram.used" || metrica.nombre == "ram.usado") {
            ram_usado_bytes = metrica.valor;
        } else if (metrica.nombre == "ram.total" || metrica.nombre == "ram.total") {
            ram_total_bytes = metrica.valor;
        } else if (metrica.nombre == "disk.used" || metrica.nombre == "disco.usado") {
            disco_usado_bytes = metrica.valor;
        } else if (metrica.nombre == "disk.total" || metrica.nombre == "disco.total") {
            disco_total_bytes = metrica.valor;
        } else if (metrica.nombre == "network.rx" || metrica.nombre == "net.rx") {
            net_rx_bytes = metrica.valor;
        } else if (metrica.nombre == "network.tx" || metrica.nombre == "net.tx") {
            net_tx_bytes = metrica.valor;
        }
    }

    // Convertir valores formateados a string para ajustarlos al ancho fijo de columna (< 80 cols)
    std::string ram_str = chuspapulse::utils::formatearBytesHumanos(ram_usado_bytes) + "/" + 
                          chuspapulse::utils::formatearBytesHumanos(ram_total_bytes);
    std::string disco_str = chuspapulse::utils::formatearBytesHumanos(disco_usado_bytes) + "/" + 
                            chuspapulse::utils::formatearBytesHumanos(disco_total_bytes);
    std::string net_str = chuspapulse::utils::formatearBytesHumanos(net_rx_bytes) + "/s/" + 
                          chuspapulse::utils::formatearBytesHumanos(net_tx_bytes) + "/s";

    std::ostringstream oss_cpu, oss_ram, oss_disco, oss_red;

    // Usar std::setw y std::left con anchos controlados (total de línea menor a 80 caracteres)
    oss << formatearTimestamp(snapshot.timestamp) << "\n"
        << std::left 
        << "  " << std::setw(10) << "CPU"   << ": " << std::setw(8)  << std::fixed << std::setprecision(1) << cpu_pct << "%\n"
        << "  " << std::setw(10) << "RAM"   << ": " << std::setw(18) << ram_str << "\n"
        << "  " << std::setw(10) << "Disco" << ": " << std::setw(18) << disco_str << "\n"
        << "  " << std::setw(10) << "Red"   << ": " << std::setw(22) << net_str;

    return oss.str();
}
