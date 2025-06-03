package crud;

import model.CategorieCarte;
import service.AuditService;
import service.DataInitialization;
import java.sql.*;
import java.util.Scanner;

public class CategoriiCartiCRUD {
    private static final Scanner scanner = new Scanner(System.in);

    public static void meniuCategorie() {
        while (true) {
            System.out.println("\n--- Meniu Categorii Carte ---");
            System.out.println("1. Adaugă categorie");
            System.out.println("2. Afișează toate categoriile (sortate)");
            System.out.println("3. Actualizează categorie");
            System.out.println("4. Șterge categorie");
            System.out.println("5. Înapoi la meniul principal");
            System.out.print("Alege opțiunea: ");

            int optiune = scanner.nextInt();
            scanner.nextLine();

            switch (optiune) {
                case 1 -> adaugaCategorie();
                case 2 -> afiseazaCategorii();
                case 3 -> actualizeazaCategorie();
                case 4 -> stergeCategorie();
                case 5 -> {
                    System.out.println("Revenire la meniul principal...");
                    return;
                }
                default -> System.out.println("Opțiune invalidă. Încearcă din nou.");
            }
        }
    }

    private static void adaugaCategorie() {
        try (Connection conn = DataInitialization.getConnection()) {
            System.out.println("\n--- Adăugare Categorie ---");
            System.out.print("Nume categorie: ");
            String nume = scanner.nextLine();

            String sql = "INSERT INTO CATEGORIE_CARTE (nume) VALUES (?)";
            PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
            stmt.setString(1, nume);
            stmt.executeUpdate();

            int id;
            try (ResultSet rs = stmt.getGeneratedKeys()) {
                rs.next();
                id = rs.getInt(1);
            }

            DataInitialization.getInstance().getCategorii().add(new CategorieCarte(id, nume));

            System.out.println("Categorie adăugată cu succes! ID: " + id);
            AuditService.logAction("ADMIN - adaugaCategorie - ID: " + id);

        } catch (SQLException e) {
            System.out.println("Eroare la adăugare categorie: " + e.getMessage());
        }
    }

    private static void afiseazaCategorii() {
        System.out.println("\n--- Lista Categorii (sortate lexicografic) ---");

        if (DataInitialization.getInstance().getCategorii().isEmpty()) {
            System.out.println("Nu există categorii înregistrate.");
            return;
        }

        DataInitialization.getInstance().getCategorii()
                .forEach(c -> System.out.printf("ID: %d | Nume: %s%n------------------------%n",
                        c.getId(), c.getNume()));
    }

    private static void actualizeazaCategorie() {
        afiseazaCategorii();
        System.out.print("\nIntrodu ID-ul categoriei de actualizat: ");
        int id = scanner.nextInt();
        scanner.nextLine();

        // Verificăm existența în memorie
        CategorieCarte categorie = DataInitialization.getInstance().getCategorii()
                .stream()
                .filter(c -> c.getId() == id)
                .findFirst()
                .orElse(null);

        if (categorie == null) {
            System.out.println("Categoria nu a fost găsită!");
            return;
        }

        try (Connection conn = DataInitialization.getConnection()) {
            System.out.println("\nIntrodu noile date:");
            System.out.print("Nume categorie (" + categorie.getNume() + "): ");
            String numeNou = scanner.nextLine();

            String sql = "UPDATE CATEGORIE_CARTE SET nume=? WHERE id=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, numeNou);
            stmt.setInt(2, id);

            if (stmt.executeUpdate() > 0) {
                // Actualizăm în memorie (TreeSet-ul se va re-sorta automat)
                DataInitialization.getInstance().getCategorii().remove(categorie);
                categorie.setNume(numeNou);
                DataInitialization.getInstance().getCategorii().add(categorie);

                System.out.println("Categorie actualizată cu succes!");
                AuditService.logAction("ADMIN - actualizeazaCategorie - ID: " + id);
            }

        } catch (SQLException e) {
            System.out.println("Eroare la actualizare categorie: " + e.getMessage());
        }
    }

    private static void stergeCategorie() {
        afiseazaCategorii();
        System.out.print("\nIntrodu ID-ul categoriei de șters: ");
        int id = scanner.nextInt();
        scanner.nextLine();

        // Verificăm existența în memorie
        CategorieCarte categorie = DataInitialization.getInstance().getCategorii()
                .stream()
                .filter(c -> c.getId() == id)
                .findFirst()
                .orElse(null);

        if (categorie == null) {
            System.out.println("Categoria nu a fost găsită!");
            return;
        }

        System.out.print("Ești sigur că vrei să ștergi categoria '" + categorie.getNume() + "'? (da/nu): ");
        if (!scanner.nextLine().equalsIgnoreCase("da")) {
            System.out.println("Ștergere anulată.");
            return;
        }

        try (Connection conn = DataInitialization.getConnection()) {
            String sql = "DELETE FROM CATEGORIE_CARTE WHERE id=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setInt(1, id);

            if (stmt.executeUpdate() > 0) {
                // Ștergem din memorie
                DataInitialization.getInstance().getCategorii().remove(categorie);
                System.out.println("Categorie ștearsă cu succes!");
                AuditService.logAction("ADMIN - stergeCategorie - ID: " + id);
            }

        } catch (SQLException e) {
            System.out.println("Eroare la ștergere categorie: " + e.getMessage());
        }
    }
}